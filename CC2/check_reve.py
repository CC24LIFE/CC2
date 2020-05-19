import os
import argparse

REVE_BIN="/home/vhui/ResearchCode/llreve/reve/build/reve/llreve"
Z3_450_BIN="/home/vhui/ResearchCode/z3-reve/z3-4.5.0-x64-ubuntu-14.04/bin/z3"
TIMEOUT = 300

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--dir', type=str, dest='dir', default=".", help="the directory of tasks")
    parser.add_argument('--clientname', type=str, dest='clientname', default="client", help="name of client function")
    args = parser.parse_args()
    result = CheckDirs(args.dir, args.clientname)
    if (result):
        print("All callsites have impact boundary, CSE")
    else:
        print("exist callsite without impact boundary, non-CSE")

def CheckDirs(dir, clientname):
    assert(os.path.isdir(dir))
    verified = set()
    callsites = [os.path.abspath(os.path.join(dir, o)) for o in os.listdir(dir) if os.path.isdir(os.path.join(dir, o)) and o.startswith("callsite_")]

    for callsite in callsites:
        cur_dir = os.path.join(callsite, "tasks")
        while (cur_dir not in verified):
            old_file = os.path.join(cur_dir, "old.c")
            new_file = os.path.join(cur_dir, "new.c")
            assert(os.path.isfile(old_file))
            assert (os.path.isfile(new_file))
            verification_result = check_eq(old_file, new_file, clientname)
            if verification_result:
                with open(os.path.join(cur_dir, "leaves.txt"), 'r') as leaves_file:
                    leaves = leaves_file.readlines()
                    for leave in leaves:
                        verified.add(leave.rstrip('\n'))
                verified.add(cur_dir)
                break
            else:
                next_dir = os.path.join(cur_dir, "tasks")
                if os.path.islink(next_dir):
                    cur_dir = os.readlink(next_dir)
                elif os.path.isdir(next_dir):
                    cur_dir = next_dir
                else:
                    return False
    return True


def check_eq(old, new, clientname):
    import shlex, subprocess
    from subprocess import PIPE, TimeoutExpired

    try:
        #runlim -o ${filename}.runlim -t 300 -s 10000 ${REVE_BIN} -fun=${clientname} -infer-marks -inline-opts -o ${filename}.smt2 -resource-dir=/usr/lib/clang/6.0.0/ -muz ${filepath}_1.c ${filepath}_2.c
        #runlim --output-file=${filename}.z3runlim -t 300 -s 10000 ${Z3_450_BIN} -smt2 fixedpoint.engine=duality ${filename}.smt2
        arg_string = "{} -fun={} -inline-opts -resource-dir=/usr/lib/clang/6.0.0/ -muz {} {}".format(REVE_BIN, clientname, old, new) #-infer-marks 
        print(arg_string)
        args0 = shlex.split(arg_string)
        proc0 = subprocess.Popen(args0, stdout=PIPE, stderr=PIPE)
        z3arg_string = "time -p {} -in -smt2 fixedpoint.engine=duality".format(Z3_450_BIN)
        print(z3arg_string)
        args = shlex.split( z3arg_string )
        proc = subprocess.Popen(args, stdin=proc0.stdout, stdout=PIPE, stderr=PIPE)
        out, err = proc.communicate(timeout=TIMEOUT)
        
        out_lines = out.decode('utf8').split('\n')
        err_lines = err.decode('utf8').split('\n')
        for errline in out_lines: print(errline)
        for errline in err_lines: print(errline)

        if "real " in err_lines[-4]: #more robust?
          TIME = float(err_lines[-4].split()[1])

        for line in out_lines:
          if "unsat" in line:
              answer = line
              RESULT = "eq"
              break
          if "sat" in line:
              answer = line
              RESULT = "neq"
        for line in out_lines:
          if "Segmentation" in line: #or "error" in line:
              answer = line
              RESULT = "err"
          if "unknown" in line and RESULT != "err":
              answer = line
              RESULT = "unknown"

    except TimeoutExpired:
        proc.kill()
        #out, err = proc.communicate()
        args = shlex.split("kill $(ps aux | grep z3 | awk '{print $2}')") 
        kill = subprocess.Popen(args, stdout=PIPE, stderr=PIPE, shell=True)
        out, err = kill.communicate(timeout=TIMEOUT)
    
    print(RESULT, ",", answer)
    return RESULT == "eq"

if __name__ == "__main__":
    main()
