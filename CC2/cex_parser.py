import sys
import argparse
import shlex, subprocess
import re
import io

bound_map = {}
default_init = None
timeout_value = 30

def get_default_init(max):
    global  default_init
    if default_init is None:
        while max >= 30:
            max = max /2
        default_init = int(max)

    return default_init


def get_cex(in_filename = "z3temp.out", out_filename = "", library="lib"):
  all_argmap = {}
  with open(in_filename, 'r+') as f:
    count = 0
    arg_list = []
    for line in f:
        if count == 0:
            res = line.rstrip()
            if res == 'unsat':
                print("Error: NO COUNTEREXAMPLES, OR ASSERTS WRONG")
                break
            elif res == 'sat':
                count = count + 1
                continue
        sanitizestr = line.rstrip().rstrip("))").lstrip("((")
        if len(sanitizestr.split()) != 2:
            #TODO: ARRAY variables should be handled here
            continue
        name = sanitizestr.split()[0].lstrip("|").rstrip("|")
        val = sanitizestr.split()[1].lstrip("\"").rstrip("\"")

        name_comp = name.split("::")
        if len(name_comp) == 2 and name_comp[1].endswith("!0@1#1"):
            funcname = name_comp[0]
            if (funcname == library):
                argname = name_comp[1].rstrip("!0@1#1")
                #print(funcname, argname, val)
                arg_list.append(argname)

                try:
                  all_argmap[funcname]
                except KeyError:
                  all_argmap[funcname] = {}
                all_argmap[funcname][argname] = val
        count = count + 1
    #import pdb; pdb.set_trace()
    for func, argmap in all_argmap.items():
        print("Function name: %s(%s)" % (func,  (',').join(arg_list)))
        print("Counterexample args:")
        for arg in arg_list:
            initval = argmap[arg]
            value = twos_comp(int('0'+initval[1:], 16), 32)
            print("\t", arg, ":", value)
            argmap[arg] = value

    return all_argmap, arg_list

def twos_comp(val, bits):
    """compute the 2's complement of int value val"""
    if (val & (1 << (bits - 1))) != 0: # if sign bit is set e.g., 8bit: 128-255
        val = val - (1 << bits)        # compute negative value
    return val

def analyze_result(result, library_name, arg_signature):
    global INDEP_INPUT_TOKEN
    all_argmap = {}
    unwinding_assertion_result = True
    failed_assertion = None
    attention_flag = False
    for line in result:
        clean = line.decode("utf-8").rstrip()
        if "unwinding assertion loop" in clean:
            if clean.endswith("FAILURE"):
                unwinding_assertion_result = False
                continue
        case_match = re.search('\[(.+\.assertion\..+)\].+FAILURE',clean)
        if failed_assertion is None and case_match:
            failed_assertion = case_match.group(1)
            continue

        elif not attention_flag and \
                failed_assertion is not None \
                and "Trace for %s:" % failed_assertion == clean:
            attention_flag = True
            continue

        elif attention_flag:
            if "Trace for " in clean:
                attention_flag = False
                continue
            else:
                case_match = re.search('%s\((.*)\).+' % library_name, clean)
                if case_match:
                    args = case_match.group(1).split(',')
                    print ("Counter example:")
                    if len(arg_signature) == 0:
                        argmap = {}
                        all_argmap[library_name] = argmap
                        print("input independent counter-example")
                        break;
                    if len(args) == len(arg_signature):
                        argmap = {}
                        for i in range(len(args)):
                            all_argmap[library_name] = argmap
                            argmap[arg_signature[i]] = args[i].strip()
                            print("%s : %s" %  (arg_signature[i], args[i].strip()))
                        break

    return (failed_assertion is None), unwinding_assertion_result, all_argmap








def launch_CBMC_cex(sourcefile, lib_args, infile = 'tempSMTLIB.smt2' ,z3output = 'z3temp.out', unwinds=100 , outfile='result.txt', library="lib",
                    incremental_bound_detection = True, timer=None, lower_bound=0, timeout = timeout_value):
    complete = True
    if sourcefile:
        if incremental_bound_detection:
            global bound_map
            default_init = get_default_init(unwinds)
            key = library+"("+','.join(lib_args)+")"
            init_unwind = bound_map.get(key, default_init)
            #in case out of dynamic budget
            if (lower_bound > unwinds):
                return {}, [], False

            while (True):
                if (init_unwind < lower_bound):
                    init_unwind = init_unwind * 2
                    if (init_unwind > unwinds):
                        init_unwind = unwinds
                    continue
                args = shlex.split(
                    "cbmc %s --unwinding-assertions --unwind %d --slice-formula --smt2 --stack-trace --verbosity 5" % (
                    sourcefile, init_unwind))
                if timer is not None:
                    timer.start()
                proc = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                try:
                    out, _ = proc.communicate(timeout=timeout)
                except subprocess.TimeoutExpired:
                    print("CBMCTO")
                    proc.kill()
                    if timer is not None:
                        timer.end()
                    return {}, [], False

                result = io.BytesIO(out)
                if timer is not None:
                    timer.end()
                assertion_passed, unwinding_passed, all_argmap = analyze_result(result, library, lib_args)
                bound_map[key] = init_unwind
                if not assertion_passed:
                    return all_argmap, lib_args, True
                elif assertion_passed and unwinding_passed:
                    return {}, lib_args, True
                else:
                    if (init_unwind == unwinds):
                        break;
                    else:
                        init_unwind = init_unwind * 2
                    if (init_unwind > unwinds):
                        init_unwind = unwinds

            print("no assertion violated within {bound} ".format(bound=init_unwind))
            return {}, [], False
        else:
            if timer is not None:
                timer.start()
            temp_filename = sourcefile + "_SMTout.smt2"
            args = shlex.split(
                "cbmc %s --no-unwinding-assertions --unwind %d --smt2 --outfile %s" % (sourcefile, unwinds, temp_filename))
            proc = subprocess.Popen(args)
            out, err = proc.communicate(timeout=180)

            args = shlex.split("z3 %s" % (temp_filename))
            with open(z3output, "w+") as out:
                proc = subprocess.Popen(args, stdout=out)
                out, err = proc.communicate(timeout=180)
            if timer is not None:
                timer.end()
            arg_map, arg_list = get_cex(z3output, outfile, library)
            return arg_map, arg_list, complete

    elif infile:
        args = shlex.split("z3 %s > %s" % (infile))
        with open(z3output, "w+") as out:
            proc = subprocess.Popen(args, stdout=out)
            out, err = proc.communicate(timeout=180)
        arg_map, arg_list = get_cex(z3output, outfile, library)
        return arg_map, arg_list, complete
    else:
        arg_map, arg_list = get_cex(library=library)
        return arg_map, arg_list, complete

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
    args = shlex.split("cbmc %s --no-unwinding-assertions --unwind %d --smt2 --outfile %s" % (sourcefile, unwinds, temp_filename))
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
    #should not happen?
