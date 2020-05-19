import argparse
from os import path
from pycparser import parse_file, c_generator, c_ast, c_parser
from copy import *



def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--new', type=str, dest='new', default="new.c", help="new source file")
    parser.add_argument('--old', type=str, dest='old', default="old.c", help="old source file")
    parser.add_argument('--client', type=str, dest='client', default="client", help="client function name")
    parser.add_argument('--lib', type=str, dest='lib', default="lib", help="lib function name")

    args = parser.parse_args()
    path_old = args.old
    path_new = args.new

    if path.isfile(path_old) and path.isfile(path_new):
        trace_program_structure(path_old, path_new, args.client, args.lib)
    else:
        print("one of the input files doesn't exist")


def trace_program_structure (path_old, path_new, client, lib):
    old_ast = parse_file(path_old, use_cpp=True,
                         cpp_path='gcc',
                         cpp_args=['-E', r'-Iutils/fake_libc_include'])
    new_ast = parse_file(path_new, use_cpp=True,
                         cpp_path='gcc',
                         cpp_args=['-E', r'-Iutils/fake_libc_include'])

    trace_tree = TraceFinder(old_ast, lib)
    trace_tree.print_trace(client=client)



def TraceFinder(node, target):
    root = TreeNode(target)
    working_list=[root]
    while len(working_list) > 0:
        item = working_list.pop()
        LPF = LibPathFinder()
        LPF.find_target(node, item)
        updated_component = LPF.temp_container
        working_list += updated_component

    return root



class TreeNode():
    def __init__(self, value):
        self.value = value
        self.parent = None
        self.children = []

    def add_child(self, value):
        if not self.is_recusive(value):
            child_node = TreeNode(value)
            self.children.append(child_node)
            child_node.parent = self
            return child_node

    def is_recusive(self, value):
        trace =  self._is_recursive(value, [value])
        if len(trace) == 0:
            return False
        else:
            print("recursive trace : " + " <- ".join(trace))
            return True


    def _is_recursive(self, value, trace):
        trace.append(self.value)
        if self.value == value:
            return trace
        else:
            if self.parent is not None:
                return self.parent._is_recursive(value, trace)
            else:
                return []

    def get_value(self):
        return self.value

    def print_trace(self, client=None):
        self._print_trace([], client=client)

    def _print_trace(self, anestor, client=None):
        anestor.append(self.get_value())
        if len(self.children) == 0:
            if (client is None or client in anestor):
                print (" <- ".join(anestor))
        else:
            for node in self.children:
                local_acestor =deepcopy(anestor)
                node._print_trace(local_acestor, client=client)



class LibPathFinder(c_ast.NodeVisitor):
    def __init__(self):
        self.target = None
        self.parent_child = {}
        self.temp_container = []

    def find_target(self, node, target):
        self.target=target
        self.visit(node)

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        for c in node:
            self.parent_child[c] = node
            self.visit(c)

    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            if (node.name.name == self.target.get_value()):
                #find the target, now look for its host function
                while not (isinstance(node, c_ast.FileAST)):
                    # stop until the file node in case nested function decl
                    if (isinstance(node, c_ast.FuncDef)):
                        c_Tnode = self.target.add_child(node.decl.name)
                        if c_Tnode is not None:
                            self.temp_container.append(c_Tnode)
                    node = self.parent_child[node]
                #Now try to find the located function def



if __name__ == '__main__':
    main()
