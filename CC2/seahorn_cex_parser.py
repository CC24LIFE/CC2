import sys
import argparse
import shlex, subprocess
import re
from pycparser import parse_file, c_generator, c_ast, c_parser

timeout_value = 60


seahorn_install = "sea"
sea_horn_verify_header = "extern void __VERIFIER_assume (int);\n" \
                         "extern void __VERIFIER_error ();\n" \
                         "__attribute__((__noreturn__)) extern void __VERIFIER_error (void);\n " \
                         "#define assert(X) if(!(X)){__VERIFIER_error ();}\n " \
                         "#define assume __VERIFIER_assume\n" \
                         "extern int nd();\n"

seahorn_cex_prefix = "@0 = private constant"
zero_init = "zeroinitializer"

nd_entry = "define i32 @nd"
inbound_text = "getelementptr inbounds"

def extract_entry_head_name(results):
    index = 0;
    activated = False
    id = None
    while index in range(len(results)):
        result = results[index]
        if not activated:
            if result.startswith(nd_entry):
                activated = True
        else:
            case_match = re.search('getelementptr inbounds \(.*(@\d).*\)', result)
            if (case_match):
                id = case_match.group(1)
                return id
            elif result == "}":
                return None
        index+=1
    return id

class InputInitVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.parent_child = {}
        self.tobeChanged=[]



    def visit_Decl(self,node):
        if isinstance(node, c_ast.Decl) and not isinstance(node, c_ast.FuncDecl):
            node.init = c_ast.FuncCall(name=c_ast.ID(name='nd'), args=c_ast.ExprList(exprs=[]))



def prepend_file(filename, prepend_text):
    parsed_file = parse_file(filename, use_cpp=True,
                         cpp_path='gcc',
                         cpp_args=['-E', r'-Iutils/fake_libc_include'])
    main_func = None
    for fundef in parsed_file.ext:
        if isinstance(fundef, c_ast.FuncDef):
            if fundef.decl.name == "main":
                main_func = fundef
                break;

    if main_func is not None:
        IIV = InputInitVisitor()
        IIV.visit(main_func.body)

    generator = c_generator.CGenerator()
    content = prepend_text + generator.visit(parsed_file)
    outfile = filename.rstrip(".c") + "_sea.c"
    with open(outfile, 'w') as of:
        of.write(content)
    return outfile

def extract_cex(cexfileName, lib_args, lib_name):
    all_argmap = {}
    all_args = []

    with open(cexfileName) as cexfile:
        cexfile_contents= cexfile.readlines()

    id = extract_entry_head_name(cexfile_contents)
    if id is not None:
        print(id)
        cex_prefix = seahorn_cex_prefix.replace("@0", id)
    else:
        cex_prefix = seahorn_cex_prefix
    cex_line =""
    for line in cexfile_contents:
        if line.startswith(cex_prefix):
            cex_line = line
            break;

    if len(cex_line) > 0:
        cexs_match = re.search('\[.*\]\s*\[(.*)\].*', cex_line)
        if cexs_match:
            cexs = cexs_match.group(1).split(',')
            if (len(cexs) >= len(lib_args)):
                argmap = {}
                all_argmap[lib_name] = argmap
                arg_num = len(lib_args)
                for i in range(arg_num):
                    argmap[lib_args[i]] = cexs[i].split()[-1]
                    print ("counterexamples: %s  = %s" % (lib_args[i],cexs[i].split()[-1] ) )
                all_args = lib_args
            else:
                argmap = {}
                all_argmap[lib_name] = argmap
                arg_num = len(cexs)
                for i in range(arg_num):
                    argmap[lib_args[i]] = cexs[arg_num-i-1].split()[-1]
                    print("counterexamples: %s  = %s" % (lib_args[i], cexs[arg_num-i-1].split()[-1]))
                for i in range(arg_num, len(lib_args)):
                    argmap[lib_args[i]] = '0'
                    print("counterexamples: %s  = %d" % (lib_args[i], 0))
                all_args = lib_args
        elif cex_line.rstrip('\n').endswith(zero_init):
            argmap = {}
            all_argmap[lib_name] = argmap
            arg_num = len(lib_args)
            for i in range(arg_num):
                argmap[lib_args[i]] ='0'
                print("counterexamples: %s  = %d" % (lib_args[i], 0))
            all_args = lib_args
        else:
            print("Error")
    else:
        print ("input independent CEX")
        argmap = {}
        all_argmap[lib_name] = argmap
        for key in lib_args:
            argmap[key] = '0'

    return all_argmap, all_args


def twos_comp(val, bits):
    """compute the 2's complement of int value val"""
    if (val & (1 << (bits - 1))) != 0:  # if sign bit is set e.g., 8bit: 128-255
        val = val - (1 << bits)  # compute negative value
    return val


def launch_seahorn_cex(sourcefile, lib_args, infile='tempSMTLIB.smt2', z3output='z3temp.out', outfile='result.txt',
                    library="lib", timer=None, timeout=timeout_value):
    if sourcefile:
        new_file = prepend_file(sourcefile, sea_horn_verify_header)
        temp_filename = sourcefile + "_cex.ll"
        args = shlex.split(
            "%s pf %s --cex=%s" % (seahorn_install, new_file, temp_filename))
        if timer is not None:
            timer.start()
        try:
            process = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True,
                                    timeout=timeout)
        except subprocess.TimeoutExpired:
            print("generalization timeout")
            if timer is not None:
                timer.end()
            return {}, lib_args
        if process.returncode < 0:
            raise subprocess.CalledProcessError(returncode=process.returncode, cmd=args)
        result = process.stdout.rstrip().split('\n')[-1]
        if timer is not None:
            timer.end()

        if "unsat" in result:
            print("No Counter examples")
            return {}, []
        elif "sat" in result:
            return extract_cex(temp_filename, lib_args, library)
            print("counter example:")

        else:
            print("error")
            return {}, []

if __name__ == "__main__":
    argv = sys.argv[1:]

    parser = argparse.ArgumentParser()
    parser.add_argument('--sourcefile', nargs='?', default=None)
    parser.add_argument('--unwinds', type=int, default=25)
    parser.add_argument('--infile', nargs='?', default='tempSMTLIB.smt2')
    parser.add_argument('--outfile', nargs='?', default=None)
    parser.add_argument('--z3output', nargs='?', default='z3temp.out')

    io_args = parser.parse_args()
    sourcefile = io_args.sourcefile
    unwinds = io_args.unwinds
    infile = io_args.infile
    z3output = io_args.z3output
    outfile = io_args.outfile

    if sourcefile:
        temp_filename = sourcefile + "_SMTout.smt2"
        args = shlex.split(
            "cbmc %s --no-unwinding-assertions --unwind %d --smt2 --outfile %s" % (sourcefile, unwinds, temp_filename))
        proc = subprocess.Popen(args)
        out, err = proc.communicate(timeout=180)

        args = shlex.split("z3 %s" % (temp_filename))
        with open(z3output, "w+") as out:
            proc = subprocess.Popen(args, stdout=out)
            out, err = proc.communicate(timeout=180)
        get_cex(z3output, outfile)

    elif infile:
        args = shlex.split("z3 %s > %s" % (infile))
        with open(z3output, "w+") as out:
            proc = subprocess.Popen(args, stdout=out)
            out, err = proc.communicate(timeout=180)
        get_cex(z3output, outfile)
    else:
        get_cex()
        # should not happen?
