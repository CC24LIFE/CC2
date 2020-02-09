from os import path
from pycparser import parse_file, c_generator, c_ast, c_parser
import copy
import shlex, subprocess

def validate(path_old, path_new, client, lib, cex, index="0"):
    if path.isfile(path_old) and path.isfile(path_new):
        try:
            test_harness, outfile = create_test_harness(path_old, path_new, client, lib , cex, index = index)
            program_name = outfile.rstrip(".c")
            args = shlex.split("gcc -O2 %s -o %s" % (outfile, program_name))
            subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
            #args = shlex.split("chmod 755 %s" % program_name)
            #subprocess.call(args)
            args = shlex.split("./%s" % program_name)
            result = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
            output = result.stdout
            if (" CEXs validated") in output:
                return 0
            else:
                return 1
        except:
            return 2

def create_test_harness(path_old, path_new, client, lib, cex, index):
    old_ast = parse_file(path_old, use_cpp=True,
                         cpp_path='gcc',
                         cpp_args=['-E', r'-Iutils/fake_libc_include'])
    new_ast = parse_file(path_new, use_cpp=True,
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
    assert not old_client_node is None, "old client not exist"
    if isinstance(old_client_node, c_ast.FuncDef):
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


    # ceate the main function
    main_func = copy.deepcopy(old_client_node)
    main_func.decl.name = "main"
    main_func.decl.type.type.declname = "main"
    main_func.decl.type.args = c_ast.ParamList(params=[])
    main_func.body.block_items = []
    calling_list = []

    if (new_client_node.decl.type.args is not None):
        assert old_client_node.decl.type.args is not None , "arg mismatch"
        assert len(new_client_node.decl.type.args.params) == len(old_client_node.decl.type.args.params), "arg mismatch"
        assert len(new_client_node.decl.type.args.params) == len(cex), "arg mismatch"
    parser = c_parser.CParser()
    if new_client_node.decl.type.args is not None:
        for i in range(len(new_client_node.decl.type.args.params)):
            decl = new_client_node.decl.type.args.params[i]
            decl_copy = copy.deepcopy(decl)
            main_func.body.block_items.append(decl_copy)
            if not decl.name is None and isinstance(decl, c_ast.Decl):
                value = cex.get(decl.name, None)
                decl_copy.init = c_ast.Constant(type=decl.type, value=value)
                calling_list.append(c_ast.ID(name=decl_copy.name))

    old_client_invo = c_ast.FuncCall(name=c_ast.ID(old_client_node.decl.name),
                                     args=c_ast.ExprList(exprs=calling_list))
    new_client_invo = c_ast.FuncCall(name=c_ast.ID(new_client_node.decl.name),
                                     args=c_ast.ExprList(exprs=calling_list))


    report_cex =  c_ast.FuncCall(name=c_ast.ID(name="printf"),
                                                     args=c_ast.ExprList(exprs=([c_ast.Constant(type='string',
                                                                                                value="\" CEXs validated \\n" + "\"")])))
    report_non_cex =  c_ast.FuncCall(name=c_ast.ID(name="printf"),
                                                     args=c_ast.ExprList(exprs=([c_ast.Constant(type='string',
                                                                                                value="\" spurious error \\n" + "\"")])))
    cond = c_ast.BinaryOp(op="!=", left=old_client_invo,
                                                                         right=new_client_invo)

    main_func.body.block_items.append(c_ast.If(cond=cond, iftrue=report_cex, iffalse=report_non_cex))


    harness_File = old_ast
    other_things = []
    for item in harness_File.ext:
        if isinstance(item, c_ast.FuncDef):
            if (item.decl.name != "main"):
                other_things.append(item)
    harness_File.ext = (other_things + [new_lib_node, new_client_node, main_func])

    generator = c_generator.CGenerator()

    output_string = "#include <stdio.h> \n" + generator.visit(harness_File)
    output_file_name = "validation_unmerged_%s.c" % index
    with open(output_file_name, "w") as outfile:
        outfile.write(output_string)
    # print(output_string)

    return harness_File, output_file_name


class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self, target):
        self.target = target
        self.container = None

    def visit_FuncDef(self, node):
        if (self.container is None and node.decl.name == self.target):
            self.container = node
            return

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