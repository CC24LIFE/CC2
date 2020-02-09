from pycparser import c_generator, c_ast
import copy

class ReturnCleanUpVistor(c_ast.NodeVisitor):
    def __init__(self):
        self.rets =[]
        self.ret_exps = []

    def visit_Return(self,node):
        if isinstance(node, c_ast.Return):
            self.rets.append(node)
            self.ret_exps.append(node.expr)

    def work(self, function_node):
        ret_num = len(self.rets)
        # if more than 1 return
        if ret_num > 1:
            if isinstance(function_node, c_ast.FuncDef):
                f_type = function_node.decl.type
                while not isinstance(f_type, c_ast.TypeDecl):
                    f_type = f_type.type
                new_type = copy.deepcopy(f_type)
                new_type.type.names = ['int']
                function_node.decl.type.type = c_ast.PtrDecl(type=new_type, quals=[])

                new_ret_decl = c_ast.Decl(name="CLEVER_RET", funcspec=[], bitsize=None, storage=[], quals=[], init=c_ast.InitList(exprs=self.ret_exps), type=c_ast.ArrayDecl(
                dim=c_ast.Constant(type='int', value=str(ret_num)), dim_quals=[], type=c_ast.TypeDecl(declname="CLEVER_RET", quals=[], type=c_ast.IdentifierType(names=['int']))))

                ret_state = c_ast.Return(expr=c_ast.ID(name=new_ret_decl.name))

                for node in self.rets:
                    function_node.body.block_items.remove(node)

                function_node.body.block_items.append(new_ret_decl)
                function_node.body.block_items.append(ret_state)

            return


def check_equivlence(client_seq, old_lib, new_lib, lib_name="lib"):

    assert not old_lib is None, "old lib does not exist"
    #if isinstance(old_lib, c_ast.FuncDef):
        #old_lib.decl.name += "_old"
        #old_lib.decl.type.type.declname += "_old"

    assert not new_lib is None, "new lib does not exist"
    #if isinstance(new_lib, c_ast.FuncDef):
        #new_lib.decl.name += "_new"
        #new_lib.decl.type.type.declname += "_new"



    generator = c_generator.CGenerator()


    old_lib_string = generator.visit(old_lib)

    new_lib_string = generator.visit(new_lib)

    for i in range(len(client_seq)):
        immediate_caller = client_seq[i].parent
        if (immediate_caller.checked):
            continue
        k = 1
        while immediate_caller is not None:
            client_node = immediate_caller.raw_node
            RCV = ReturnCleanUpVistor()
            RCV.visit(client_node)
            RCV.work(client_node)
            #new_client_node = copy.deepcopy(old_client_node)
            #LHR_new = LibInvoHunter_Reanme(lib_name, "new")
            #LHR_new.visit(new_client_node)
            #LHR_old = LibInvoHunter_Reanme(lib_name, "old")
            #LHR_old.visit(old_client_node)

            old_file_name ="MLC_{d}_old.c".format(d=k)
            with open(old_file_name, 'w') as outfile:
                outfile.write(old_lib_string)
                outfile.write(generator.visit(client_node))

            new_file_name ="MLC_{d}_new.c".format(d=k)
            with open(new_file_name, 'w') as outfile:
                outfile.write(new_lib_string)
                outfile.write(generator.visit(client_node))

            immediate_caller = immediate_caller.parent
            k+=1



    return client_seq