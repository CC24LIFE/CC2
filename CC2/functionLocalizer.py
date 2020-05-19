import argparse
from os import path
from pycparser import parse_file, c_generator, c_ast, c_parser

FunctionNodes = dict()
FunctionCallNodes = dict()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--file', type=str, dest='file', default="file.c", help="target file to parse for input")

    args = parser.parse_args()
    file_path = args.file

    if path.isfile(file_path):
        get_valid_input(file_path)
    else:
        print("input file doesn't exist")

def get_valid_input(file_path):
    generator = c_generator.CGenerator()
    file_ast = parse_file(file_path, use_cpp=True,
                         cpp_path='gcc',
                         cpp_args=['-E', r'-Iutils/fake_libc_include'])

    FDH = FunDefHunter()
    all_func = FDH.getallFunDef(file_ast)

    #now build a function call graph
    for func in all_func:
        func_node = create_tree_node(func)
        FCH = FuncCallHunter()
        callees = FCH.getallFunCall(func)
        for callee_name in callees:
            callee = retrive_funcdeff_by_name(all_func, callee_name)
            if callee is not None:
                func_node.add_child(callee)

    #roots_list = find_roots()
    #leaves_list = find_leaves()
    correction = False
    #stop until fix point
    while not correction:
        correction = True
        for func_def_node_value in all_func:
            DUV = DUVisitor()
            DUV.visit(func_def_node_value)
            #print (DUV.missing_define)
            for miss_def in DUV.missing_define:
                correction = False
                #add paramters
                if func_def_node_value.decl.type.args is None:
                    func_def_node_value.decl.type.args = c_ast.ParamList(params=[])
                func_def_node_value.decl.type.args.params.append(
                c_ast.Decl(name=miss_def, quals=[], storage=[], init=None, funcspec=[], bitsize=None,
                                                           type=c_ast.TypeDecl(declname=miss_def, quals=[], type=c_ast.IdentifierType(['int']))))
                #add arguments
                func_name = func_def_node_value.decl.name
                invocs = FunctionCallNodes.get(func_name, set())
                ID = c_ast.ID(name= miss_def)
                for invo in invocs:
                    if (isinstance(invo, c_ast.FuncCall)):
                        if invo.args is None:
                            invo.args = c_ast.ExprList(exprs=[])
                        invo.args.exprs.append(ID)

    print(generator.visit(file_ast))

    return True

def find_roots():
    roots_list = []
    global FunctionNodes
    for node_value in FunctionNodes.keys():
        node = FunctionNodes[node_value]
        if node.parent == None:
            roots_list.append(node)

    return roots_list

def find_leaves():
    leaves_list = []
    global FunctionNodes
    for node_value in FunctionNodes.keys():
        node = FunctionNodes[node_value]
        if len(node.children) == 0:
            leaves_list.append(node)

    return leaves_list


def create_tree_node(value):
    global FunctionNodes
    if value in FunctionNodes.keys():
        return FunctionNodes.get(value)
    else:
        return TreeNode(value)

def retrive_funcdeff_by_name (all_func, target):
    for func in all_func:
        if (isinstance(func, c_ast.FuncDef)):
            if func.decl.name == target:
                return func

    return None


class TreeNode():
    def __init__(self, value):
        global FunctionNodes
        self.value = value
        self.parent = None
        self.children = []
        self.recursive_trace =[]
        FunctionNodes[value] = self

    def add_child(self, value):
        if value not in self.children:
            child_node = create_tree_node(value)
            self.children.append(child_node)
            child_node.parent = self
            return child_node

    def get_value(self):
        return self.value


class FunDefHunter(c_ast.NodeVisitor):
    def __init__(self):
        self.container =[]

    def getallFunDef(self, node):
        self.container = []
        self.visit(node)
        return self.container


    def visit_FuncDef(self, node):
        if isinstance(node, c_ast.FuncDef):
            self.container.append(node)
        self.generic_visit(node)


class FuncCallHunter(c_ast.NodeVisitor):
    def  __init__(self):
        self.container = set()

    def getallFunCall(self, node):
        self.container = set()
        self.visit(node)
        return self.container

    def visit_FuncCall(self, node):
        global FunctionCallNodes
        if (isinstance(node, c_ast.FuncCall)):
            call_name = node.name.name
            self.container.add(call_name)
            invocs = FunctionCallNodes.get(call_name, set())
            invocs.add(node)
            FunctionCallNodes[call_name] = invocs
        self.generic_visit(node)


class DUVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.define = set()
        self.missing_define = set()
        self.value_changed = set()

    def check_and_refine(self, use):
        if (use is None):
            return
        if isinstance(use, str):
            if use not in self.define and use not in self.missing_define:
                self.missing_define.add(use)
        else:
            IDH = IDhunter()
            IDH.visit(use)
            for use in IDH.container:
                if use not in self.define and use not in self.missing_define:
                    self.missing_define.add(use)


    def add_to_define(self, target):
        if (target is None):
            return
        if isinstance(target, str):
            self.define.add(target)
        if isinstance(target.name, str):
            self.define.add(target.name)
        else:
            IDH = IDhunter()
            IDH.visit(target)
            for target in IDH.container:
                self.define.add(target)


    def add_to_changed(self, target):
        if (target is None):
            return
        if isinstance(target, str):
            self.value_changed.add(target)
        else:
            IDH = IDhunter()
            IDH.visit(target)
            for target in IDH.container:
                self.value_changed.add(target)



    def visit_Assignment(self, node):
        if isinstance(node, c_ast.Assignment):
            if node.lvalue is not None:
                self.check_and_refine(node.lvalue)
                self.add_to_changed(node.lvalue)

            if node.rvalue is not None:
                self.check_and_refine(node.rvalue)



    def visit_UnaryOp(self, node):
        if isinstance(node, c_ast.UnaryOp):
            if (node.op.endswith("--") or node.op.endswith("++") ):
                self.add_to_changed(node.expr)
                self.check_and_refine(node.expr)

            elif node.expr is not None:
                self.check_and_refine(node.expr)


    def visit_Decl(self, node):
        if isinstance(node, c_ast.Decl):
            self.add_to_define(node)
            if node.type is not None and isinstance(node.type, c_ast.FuncDecl):
                self.visit(node.type)
            if node.init is not None:
                self.check_and_refine(node.init)


    def visit_BinaryOp(self,node):
        if isinstance(node, c_ast.BinaryOp):
            if node.left is not None:
                self.check_and_refine(node.left)
            if node.right is not None:
                self.check_and_refine(node.right)


    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            self.check_and_refine(node.args)

    def visit_ArrayRef(self, node):
        if isinstance(node, c_ast.ArrayRef):
            self.check_and_refine(node.subscript)
        self.generic_visit(node)

class IDhunter(c_ast.NodeVisitor):
    def __init__(self):
        self.container = set()

    def visit_ID(self, node):
        if isinstance(node, c_ast.ID):
            self.container.add(node.name)

    def visit_FuncCall(self, node):
        if node.args is not None:
            self.visit(node.args)

if __name__ == '__main__':
    main()


