import argparse
from os import path
from pycparser import parse_file, c_generator, c_ast
import shlex, subprocess
import copy
import sys
import time
sys.setrecursionlimit(3000)


Klee_Header_String = "extern void klee_make_symbolic(void *addr , unsigned int nbytes , char *name ) ;\n" \
                     "extern void klee_assume(int cond ) ;\n" \
                     "extern int ( /* missing proto */  assert)() ;\n" \
                     "#include <stdio.h>\n"

def main():

    timer = Timer()

    parser = argparse.ArgumentParser()
    parser.add_argument('--new', type=str, dest='new', default="new.c", help ="new source file" )
    parser.add_argument('--old', type=str, dest ='old', default="old.c", help="old source file")
    parser.add_argument('--client', type=str, dest ='client', default="client", help="client function name" )
    parser.add_argument('--lib', type=str, dest='lib', default="lib", help="lib function name")
    parser.add_argument('--unwind', type=int, dest='unwind', default=100, help="unwind  bound for bounded model checking")

    args = parser.parse_args()
    path_old = args.old
    path_new = args.new
    test_harness = None
    if path.isfile(path_old) and path.isfile(path_new):
        timer.start()
        test_harness, outfile = create_test_harness(path_old, path_new, args.client, args.lib)
        args = shlex.split("clang-6.0 -emit-llvm -c %s" % outfile)
        subprocess.call(args)
        args = shlex.split("klee -optimize -write-no-tests -exit-on-error-type=Abort -entry-point=%s %s" % ("CLEVER_main", outfile.rstrip('c')+"bc"))
        result = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        output = result.stdout
        cex_lines = []
        outlines = output.split('\n')
        timer.end()
        print ("time : %f\n" % timer.get_time())
        eq = True
        for line in outlines:
            if "CLEVER NEQ" in line:
                eq = False
            if line.startswith("CEX "):
                cex_lines.append(line)
        if len(cex_lines) > 0 :
            print ('\n'.join(cex_lines))
        else:
            if eq:
                print ("CSE")
            else:
                print ("input independent NEQ CEX")

    else:
        print("invalid inputs")

    return test_harness

class LibInvoHunter_Reanme(c_ast.NodeVisitor):
    def __init__(self, name, version):
        self.lib = name
        self.version = version

    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            if (node.args is not None):
                self.visit(node.args)
            if isinstance(node.name, c_ast.ID) and node.name.name == self.lib:
                node.name.name += ("_" + self.version)





def create_test_harness(path_old, path_new, client, lib):
    old_ast = parse_file(path_old, use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', r'-Iutils/fake_libc_include'])
    new_ast = parse_file(path_new,use_cpp=True,
            cpp_path='gcc',
            cpp_args=['-E', r'-Iutils/fake_libc_include'])

    old_lib_visitor = FuncDefVisitor(lib)
    old_lib_visitor.visit(old_ast)
    old_lib_node = old_lib_visitor.container
    assert not old_lib_node is None, "old lib does not exist"
    if isinstance(old_lib_node, c_ast.FuncDef):
        old_lib_node.decl.name += "_old"
        old_lib_node.decl.type.type.declname += "_old"

    old_client_visitor = FuncDefVisitor(client)
    old_client_visitor.visit(old_ast)
    old_client_node = old_client_visitor.container
    assert not old_client_node is None, "old lib client not exist"
    if isinstance(old_lib_node, c_ast.FuncDef):
        old_client_node.decl.name += "_old"
        old_client_node.decl.type.type.declname += "_old"

    new_lib_visitor = FuncDefVisitor(lib)
    new_lib_visitor.visit(new_ast)
    new_lib_node = new_lib_visitor.container
    assert not new_lib_node is None, "new lib does not exist"
    if isinstance(new_lib_node, c_ast.FuncDef):
        new_lib_node.decl.name += "_new"
        new_lib_node.decl.type.type.declname += "_new"

    new_client_visitor = FuncDefVisitor(client)
    new_client_visitor.visit(new_ast)
    new_client_node = new_client_visitor.container
    assert not new_client_node is None, "new client does not exist"
    if isinstance(new_client_node, c_ast.FuncDef):
        new_client_node.decl.name += "_new"
        new_client_node.decl.type.type.declname += "_new"

    LHR_new = LibInvoHunter_Reanme(lib, "new")
    LHR_new.visit(new_client_node)
    LHR_old = LibInvoHunter_Reanme(lib, "old")
    LHR_old.visit(old_client_node)

    #ceate the main function
    main_func = copy.deepcopy(old_client_node)
    main_func.decl.name = "CLEVER_main"
    main_func.decl.type.type.declname ="CLEVER_main"
    main_func.decl.type.args = c_ast.ParamList(params=[])
    main_func.body.block_items =[]
    calling_list = []
    if new_client_node.decl.type.args is not None:
        for decl in new_client_node.decl.type.args.params:
            main_func.body.block_items.append(copy.deepcopy(decl))
            if not decl.name is None:
                main_func.body.block_items.append(make_klee_symbolic(decl.name, decl.name))
                calling_list.append(c_ast.ID(name=decl.name))


    old_client_invo = c_ast.FuncCall(name=c_ast.ID(old_client_node.decl.name), args=c_ast.ExprList(exprs=calling_list))
    new_client_invo = c_ast.FuncCall(name=c_ast.ID(new_client_node.decl.name), args=c_ast.ExprList(exprs=calling_list))

    format_string = ""
    ID_list= []
    for arg in calling_list:
        arg_name = arg.name
        format_string += "CEX {name} : %d,".format(name=arg_name)
        ID_list.append(c_ast.FuncCall(name=c_ast.ID(name="klee_get_valued"), args=c_ast.ExprList(exprs=[c_ast.ID(name=arg_name)])))
    format_string = format_string.rstrip(",")



    main_func.body.block_items.append(c_ast.FuncCall(name=c_ast.ID(name= "klee_assume"), args=c_ast.BinaryOp(op="!=", left=old_client_invo, right=new_client_invo)))
    main_func.body.block_items.append(c_ast.FuncCall(name=c_ast.ID(name="printf"),
                                                     args=c_ast.ExprList(exprs=([c_ast.Constant(type='string',
                                                                                                value="\" CLEVER NEQ \\n" + "\"")]))))
    main_func.body.block_items.append(c_ast.FuncCall(name=c_ast.ID(name="printf"),
                                                     args=c_ast.ExprList(exprs=([c_ast.Constant(type='string', value="\"" + format_string +"\\n" +"\"")] + ID_list))))
    main_func.body.block_items.append(c_ast.FuncCall(name=c_ast.ID(name="abort"),
                                                args=c_ast.ExprList(exprs=[])))
    harness_File = old_ast
    harness_File.ext = (harness_File.ext + [new_lib_node ,new_client_node, main_func])

    generator = c_generator.CGenerator()

    output_string = Klee_Header_String + generator.visit(harness_File)
    output_file_name = "klee_unmerged.c"
    with open(output_file_name, "w") as outfile:
        outfile.write(output_string)
    #print(output_string)



    return harness_File, output_file_name


def make_klee_symbolic(variable_name, trackingName):
    arg1 = c_ast.UnaryOp(op='&', expr=c_ast.ID(variable_name))
    arg2 = c_ast.UnaryOp(op='sizeof', expr = c_ast.Typename(name=None, quals =[],
                                                            type= c_ast.TypeDecl(declname=None,quals=[],
                                                                                 type=c_ast.IdentifierType(names=['int']))))
    arg3 = c_ast.Constant(type='string', value='\"'+ trackingName +'\"')
    return c_ast.FuncCall(name=c_ast.ID(name = "klee_make_symbolic"), args=c_ast.ExprList(exprs=[arg1,arg2,arg3]))

class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self, target):
        self.target = target
        self.container = None

    def visit_FuncDef(self, node):
        if (self.container is None and node.decl.name == self.target):
            self.container = node
            return

class Timer(object):
    def __init__(self):
        self.interval_time = 0.0
        self.start_timer = 0.0

    def start(self):
        self.start_timer = time.time()

    def end(self):
        self.interval_time += time.time() - self.start_timer
        self.start_timer = 0.0

    def get_time(self):
        return self.interval_time


if __name__ == "__main__":
        main()


