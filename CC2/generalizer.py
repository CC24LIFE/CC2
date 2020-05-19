import shlex, subprocess
import re, os
from pycparser import parse_file, c_generator, c_ast
import ctypes

MLScript_location = os.path.join(os.path.dirname(__file__), "_build/instKlee.cma")
template_string = 'CILLY=cilly\nCLANG=clang-6.0\nKLEE=klee\nCOPTS=-Wno-attributes\nINSTKLEE={MLScript}\n# if instKlee has been installed, you can also use:\n# INSTKLEE=instKlee\n\nexport CIL_FEATURES=cil.oneret\n\n.PHONY: all clean\n\n{SOURCENAME}:{SOURCENAME}.c\n\t$(CILLY) $(COPTS) --save-temps --noPrintLn -c --load=$(INSTKLEE) --doinstKlee --entry={LIBNAME}  {ASSUMPTIONS} {SOURCENAME}.c\n\nclean:\n\trm -rf *.o *.i *.cil.* klee-*\n'
type_dict={}

def record_type_dict(types):
    global  type_dict
    type_dict = types

def get_type(name):
    global type_dict
    type = type_dict.get(name, None)
    if type is not None:
        return type
    elif name.endswith("_old") or name.endswith("_new"):
        type = type_dict.get(name[:-4], None)
        if type is not None:
            return type

    return ['int']

def twos_comp(val, bits):
    """compute the 2's complement of int value val"""
    if (val & (1 << (bits - 1))) != 0: # if sign bit is set e.g., 8bit: 128-255
        val = val - (1 << bits)        # compute negative value
    return val

def generalize(source, libname, cex_args, timer=None, lock=None):
    assumption_list = []
    for arg, cex in cex_args.items():
        type = get_type(arg)
        if type[0] == 'unsigned' and type[1] =='int' and not cex.endswith('u'):
            assumption_list.append(' == '.join([arg, repr(ctypes.c_uint(int(cex)).value)]))
        else:
            assumption_list.append(' == '.join([arg, repr(cex)]))
    assumptions = ' & '.join(assumption_list)
    if len(assumptions) >0:
        assumptions="--assume='{ass}'".format(ass=assumptions)
    makeString = template_string.format(SOURCENAME = source, ASSUMPTIONS=assumptions, LIBNAME=libname, MLScript = MLScript_location)
    lock_actions(lock)
    with open("Makefile", 'w') as makeFile:
        makeFile.write(makeString)
    subprocess.call("make")
    unclock_actions(lock)
    args = shlex.split("clang-6.0 -emit-llvm -c %s.cil.c" %source )
    subprocess.call(args)
    args = shlex.split("klee -write-no-tests -single-path=true -entry-point=%s %s.cil.bc" % (libname, source))
    if timer is not None:
        timer.start()
    result = subprocess.run(args,stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    if timer is not None:
        timer.end()
    output = result.stderr
    new_pe = PEpair(output)
    #print(new_pe.get_parition())
    #print(new_pe.get_effect_new())
    #print(new_pe.get_effect_old())
    return new_pe

def generalize_client(source, clientname, is_inlined = True, num_ret=1, lib_name ="lib", timer= None, lock=None):
    makeString = template_string.format(SOURCENAME=source, ASSUMPTIONS='', LIBNAME=clientname, MLScript = MLScript_location)
    lock_actions(lock)
    with open("Makefile", 'w') as makeFile:
        makeFile.write(makeString)
    subprocess.call("make")
    unclock_actions(lock)
    if is_inlined:
        with open(source+".cil.c", 'r') as cil_file:
            cil_file_content = cil_file.read()
            cil_file_content = cil_file_content.replace("pesudo_klee_make_symbolic", "garbage",1)
            cil_file_content = cil_file_content.replace("pesudo_klee_make_symbolic", "klee_make_symbolic").replace(" assert(", " klee_assume(")

        with open(source+".cil.c", 'w') as cil_file:
            cil_file.write(cil_file_content)
    else:
        cil_file_name = source+".cil.c"
        client_file = parse_file(cil_file_name, use_cpp=True,
                                 cpp_path='gcc',
                                 cpp_args=['-E', r'-Iutils/fake_libc_include'])
        LIV = LibInvocVisitor(lib_name)
        LIV.visit(client_file)
        LIV.work()
        generator = c_generator.CGenerator()
        with open(source+".cil.c", 'w') as cil_file:
            cil_file.write(generator.visit(client_file).replace(" assert(", " klee_assume(").replace(" //assert(", " assert(", 1).replace("extern int klee_assume();", "//extern int klee_assume();", 1))

    args = shlex.split("clang-6.0 -emit-llvm -c %s.cil.c" % source)
    subprocess.call(args)
    args = shlex.split("klee -write-no-tests -entry-point=%s %s.cil.bc" % (clientname, source))
    if timer is not None:
        timer.start()
    result = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    if timer is not None:
        timer.end()
    if result.returncode < 0:
        raise subprocess.CalledProcessError(returncode=result.returncode, cmd=args)
    output = result.stderr
    new_pe = PEClientPair(output, num_ret, is_inlined)
    #print(new_pe.get_client_specific_assertions())
    return new_pe

def generalize_pre_client(source, clientname, is_inlined = True, num_ret=1, arg_list =[] , lib_name="lib", timer= None, lock=None):
    lock_actions(lock)
    makeString = template_string.format(SOURCENAME=source, ASSUMPTIONS='', LIBNAME=clientname, MLScript = MLScript_location)
    with open("Makefile", 'w') as makeFile:
        makeFile.write(makeString)
    subprocess.call("make")
    unclock_actions(lock)
    cil_file_name = source+".cil.c"
    client_file = parse_file(cil_file_name, use_cpp=True,
                             cpp_path='gcc',
                             cpp_args=['-E', r'-Iutils/fake_libc_include'])
    KEV = KleeSymbolExternalize("_CLEVER_EXT")
    KEV.visit(client_file)
    LIPV = LibPreInvoVisitor(arg_list, lib_name)
    LIPV.visit(client_file)
    LIPV.work()
    generator = c_generator.CGenerator()
    with open(source+".cil.c", 'w') as cil_file:
        cil_file.write(generator.visit(client_file).replace(" assert(", " //assert(").replace(" //assert(", " assert(", 1))

    args = shlex.split("clang-6.0 -emit-llvm -c %s.cil.c" % source)
    subprocess.call(args)
    args = shlex.split("klee -write-no-tests -entry-point=%s %s.cil.bc" % (clientname, source))
    if timer is not None:
        timer.start()
    result = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    if timer is not None:
        timer.end()
    output = result.stderr
    new_pe = PEClientPrePair(output, arg_list)
    return new_pe

class KleeSymbolExternalize(c_ast.NodeVisitor):
    def __init__(self, keyword):
        self.keyword = keyword

    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            if isinstance(node.name, c_ast.ID) and node.name.name == "klee_make_symbolic":
                if isinstance(node.args, c_ast.ExprList) and len(node.args.exprs) == 3:
                    target = node.args.exprs[2]
                    if isinstance(target, c_ast.Constant):
                        if not target.value.endswith(self.keyword + '\"'):
                            target.value =target.value.rstrip('\"') + ("_{ext}\"".format(ext=self.keyword))


class LibPreInvoVisitor(c_ast.NodeVisitor):
    def __init__(self, arg_list, lib_name):
        self.parent_child = {}
        self.tobeInsertedBefore = []
        self.invoc = []
        self.arg_list = arg_list
        self.lib_name = lib_name
        self.old_hit = False
        self.new_hit = False

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        for c in node:
            self.parent_child[c] = node
            self.visit(c)

    def visit_FuncCall(self,node):
        if isinstance(node, c_ast.FuncCall):
            if (node.name.name ==  (self.lib_name + "_old") or node.name.name ==  (self.lib_name + "_new")):
                post_fix = node.name.name[4:]
                parent = self.parent_child.get(node, None)
                if parent is not None and isinstance(parent, c_ast.Assignment):
                    if node.name.name == (self.lib_name + "_old"):
                        self.old_hit = True
                    elif node.name.name == (self.lib_name + "_new"):
                        self.new_hit = True
                    grandparent = self.parent_child.get(parent, None)
                    if grandparent is not None and isinstance(grandparent, c_ast.Compound):
                        if node.args is not None:
                            for i in range(len(node.args.exprs)):
                                input_variable_name = "input_{d}_".format(d=self.arg_list[i].name)+post_fix
                                input_variable = c_ast.ID(name="input_{d}_".format(d=self.arg_list[i].name)+post_fix)
                                self.tobeInsertedBefore.append((grandparent, parent, c_ast.Decl(name=input_variable_name, quals=[], storage=[], init=None, funcspec=[],
                           bitsize=None,
                           type=c_ast.TypeDecl(declname=input_variable_name, quals=[],
                                               type=c_ast.IdentifierType(['int'])))))
                                self.tobeInsertedBefore.append((grandparent, parent, make_klee_symbolic(input_variable_name, input_variable_name)))
                                self.tobeInsertedBefore.append((grandparent, parent, c_ast.Assignment(op='=',lvalue=input_variable, rvalue= node.args.exprs[i])))
                                self.invoc.append((grandparent, parent))


    def work(self):
        for grandparent, parent, new_child in self.tobeInsertedBefore:
            parent_index = grandparent.block_items.index(parent)
            if parent_index >= 0:
                grandparent.block_items.insert(parent_index, new_child)

        for grandparent, parent in self.invoc:
            try:
                parent_index = grandparent.block_items.index(parent)
                if parent_index >= 0:
                    grandparent.block_items.remove(parent)
            except:
                continue



class LibInvocVisitor(c_ast.NodeVisitor):
    def __init__(self, lib_name):
        self.parent_child = {}
        self.tobeInserted=[]
        self.lib_name = lib_name

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        for c in node:
            self.parent_child[c] = node
            self.visit(c)

    def visit_FuncCall(self,node):
        if isinstance(node, c_ast.FuncCall):
            if (node.name.name == (self.lib_name+ "_old") or node.name.name == (self.lib_name + "_new")):
                post_fix = node.name.name[4:]
                parent = self.parent_child.get(node, None)
                if parent is not None and isinstance(parent, c_ast.Assignment):
                    grandparent = self.parent_child.get(parent, None)
                    if grandparent is not None and isinstance(grandparent, c_ast.Compound):
                        self.tobeInserted.append((grandparent, parent, make_klee_symbolic(parent.lvalue.name, "delta_CLEVER_ret_0_"+post_fix)))


    def work(self):
        for grandparent, parent, new_child in self.tobeInserted:
            parent_index = grandparent.block_items.index(parent)
            if parent_index>=0:
                grandparent.block_items.insert(parent_index+1, new_child)



def make_klee_symbolic(variable_name, trackingName):
    arg1 = c_ast.UnaryOp(op='&', expr=c_ast.ID(variable_name))
    arg2 = c_ast.UnaryOp(op='sizeof', expr = c_ast.Typename(name=None, quals =[],
                                                            type= c_ast.TypeDecl(declname=None,quals=[],
                                                                                 type=c_ast.IdentifierType(names=['int']))))
    arg3 = c_ast.Constant(type='string', value='\"'+ trackingName +'\"')
    return c_ast.FuncCall(name=c_ast.ID(name = "klee_make_symbolic"), args=c_ast.ExprList(exprs=[arg1,arg2,arg3]))


class PEClientPrePair(object):
    def __init__(self, pe_result, arg_lists):
        self.pre_path_constraints = set()
        pe_set = pe_result.split("Partition:")
        for pe in pe_set:
            if len(pe) > 0:
                pe_list = pe.split('\n')
                partitions = pe_list[0].split('&')
                pre_parition = []
                for part in partitions:
                    if  part != ' )  ':
                        pre_parition.append(part)

                effect_list=[]
                for k in range(len(pe_list)):
                    clean = pe_list[k][7:]

                    match_input = re.search(' (input_.+)_new\s*=\s*(.*)', clean)
                    if match_input:
                        lhs = match_input.group(1).replace("input_","")
                        effect_list.append(lhs + " == " + match_input.group(2))

                if len(effect_list) > 0:
                    pre_parition += effect_list
                    self.pre_path_constraints.add("( " + ' & '.join(pre_parition) + " )")

        #if pre_path constraint is empty by now, then library is unreachable
        if (len(self.pre_path_constraints) == 0):
            self.pre_path_constraints.add("false")

    def get_preconditions(self):
        return self.pre_path_constraints




class PEClientPair(object):
    def __init__(self, pe_result, num_ret, is_inlined):
        self.base_assumptions = set()
        self.post_path_constraints = []
        self.delta_set=()
        self.is_inlined = is_inlined
        self.empty = True
        for i in range(num_ret):
            self.base_assumptions.add(("CLEVER_ret_{d}_old".format(d=i), "CLEVER_ret_{d}_new".format(d=i)))
        pe_set = pe_result.split("Partition:")
        for pe in pe_set:
            if len(pe) > 0:
                pe_list = pe.split('\n')
                partitions = pe_list[0].split('&')
                post_parition = []
                for part in partitions:
                    if "delta_" in part:
                        post_parition.append(part.replace("delta_",""))

                effect_dict ={}
                for k in range(len(pe_list)):
                    clean = pe_list[k][7:]
                    #clean = clean.replace("delta_","")
                    if (self.empty and "Effect:" in pe_list[k]):
                        self.empty = False
                    match_old = re.search(' (CLEVER_ret_\d_old)\s*=\s*(.*)', clean)
                    match_new = re.search(' (CLEVER_ret_\d_new)\s*=\s*(.*)', clean)
                    if match_old:
                        self.empty = False
                        effect_dict[match_old.group(1)] = match_old.group(2).replace("delta_", "")
                    elif match_new:
                        self.empty = False
                        effect_dict[match_new.group(1)] = match_new.group(2).replace("delta_", "")


                processed = set()
                post_effect_eq = []
                for key, value in effect_dict.items():
                    if (key not in processed):
                        if key.endswith("_old"):
                            co_key = key.rstrip("_old") + "_new"
                        elif key.endswith("_new"):
                            co_key = key.rstrip("_new") + "_old"
                        co_value = effect_dict.get(co_key, "true")
                        if value != co_value:
                            effect_eq_constriant = (value + " == " + co_value)
                            post_effect_eq.append(effect_eq_constriant)
                            #print(effect_eq_constriant)
                            processed.add(key)
                            processed.add(co_key)
                merged_list = post_parition + post_effect_eq
                if len(merged_list) > 0:
                    self.post_path_constraints.append("(" + '&'.join(merged_list) +")" )





    def get_client_specific_assertions(self):
        return '|'.join(self.post_path_constraints)

    def get_base_assumption(self):
        result = []
        for item in self.base_assumptions:
            result.append("(" + item[0] + " == " + item[1] + ")")
        return ['&'.join(result)]

    def get_post_assertion_list(self):
        if len(self.post_path_constraints) == 0 and self.empty:
            return ["true"]
        else:
            return self.post_path_constraints









class PEpair(object):
    def __init__(self, parition_effect):
        parition_effects = parition_effect.split('\n')
        self.parition = ""
        i = 0
        condition_over = False
        condition_list = set()
        while (i< len(parition_effects) and not condition_over):
            line = parition_effects[i]
            if (line.startswith('Condition:')):
                condition = line.strip('Condition:').strip()
                condition_list.add(condition)
                i+=1
            else:
                condition_over = True
        self.parition = "&".join(condition_list)
        self.new_effect = {}
        self.old_effect = {}
        for k in range(i, len(parition_effects)):
                clean =  parition_effects[k][7:]
                match_old = re.search('(CLEVER_ret_\d_old).*',clean)
                match_new = re.search('(CLEVER_ret_\d_new).*',clean)
                if match_old:
                    self.old_effect[match_old.group(1)] = clean
                elif match_new:
                    self.new_effect[match_new.group(1)]= clean

    def get_parition(self):
        return self.parition

    def get_effect_old(self):
        return self.old_effect

    def get_effect_new(self):
        return self.new_effect

def lock_actions(lock):
    if lock is not None :
        lock.acquire()

def unclock_actions(lock):
    if lock is not None :
        lock.release()


if __name__ =="__main__":

    print (template_string.format(SOURCENAME = "merged", ASSUMPTIONS="a == 5", LIBNAME="lib", MLScript = MLScript_location))

    '''
    with open("MakeTemplate", "r") as templateFile:
      templateString = templateFile.read()
      print(repr(templateString))
    '''