from pycparser import c_ast
from CC2 import checker
import copy
is_MLCCheker = True


type_dict={}

def record_type_dict(types):
    global  type_dict
    type_dict = types


def analyze_client(client_node, lib):
    CFV = ClientFUnctionHierarchyVisitor (lib, client_node)
    CFV.visit(client_node)
    return CFV.leaves

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

'''
Given a fragment of C functions, complete the function by adding approipate input variables
'''
def complete_functions(func_object, client_template, lib, is_MLCCheker =True):
    if not is_MLCCheker:
        func = func_object.raw_node
        if not isinstance(func, c_ast.FuncDef):
            DUV = DUVisitor()
            DUV.visit(func)
            new_func = copy.deepcopy(client_template)

            new_func.decl.name = client_template.decl.name
            renamed_type =new_func.decl.type
            template_type =client_template.decl.type
            while not isinstance(template_type, c_ast.TypeDecl):
                renamed_type = renamed_type.type
                template_type = template_type.type
            renamed_type.declname = template_type.declname
            new_func.decl.type.args = c_ast.ParamList([])
            new_func.body.block_items = []
            new_func.body.block_items.append(copy.deepcopy(func))
            for missing_def in DUV.missing_define:
                new_func.decl.type.args.params.append(
                    c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                               bitsize=None,
                               type=c_ast.TypeDecl(declname=missing_def, quals=[],
                                                   type=c_ast.IdentifierType(get_type(missing_def)))))

                if missing_def in DUV.value_changed:
                    new_func.body.block_items.append(c_ast.Return(c_ast.ID(missing_def)))
        else:
            new_func = func

        func_object.raw_node = new_func

    func = func_object.node
    if not isinstance(func, c_ast.FuncDef):
        DUV = DUVisitor()
        DUV.visit(func)
        new_func = copy.deepcopy(client_template)

        new_func.decl.name = client_template.decl.name
        renamed_type = new_func.decl.type
        template_type = client_template.decl.type
        while not isinstance(template_type, c_ast.TypeDecl):
            renamed_type = renamed_type.type
            template_type = template_type.type
        renamed_type.declname = template_type.declname
        new_func.decl.type.args = c_ast.ParamList([])
        new_func.body.block_items = []
        new_func.body.block_items.append(copy.deepcopy(func))
        for missing_def in DUV.missing_define:
            new_func.decl.type.args.params.append(
                                                c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                                                           bitsize=None,
                                                           type=c_ast.TypeDecl(declname=missing_def, quals=[],
                                                                               type=c_ast.IdentifierType(['int']))))

            if missing_def in DUV.value_changed:
                new_func.body.block_items.append(c_ast.Return(c_ast.ID(missing_def)))
        #if func is a just a program segment, then also add local variables
        if isinstance(func, c_ast.Compound):
            for value_changed in DUV.value_changed:
                if value_changed not in DUV.missing_define:
                    new_func.body.block_items.append(c_ast.Return(c_ast.ID(value_changed)))
    else:
        new_func = func

    func_object.node = checker.version_merge_client(new_func, lib)
    set_of_define_interest = set()
    set_of_change_define_interest =set()
    if func_object.arg_lib is not None and isinstance(func, c_ast.FuncDef):
        temp_client_func = func_object.node
        CUV = CleanUpVisitor()
        CUV.visit(temp_client_func)
        DUV = DUVisitor()
        DUV.visit(temp_client_func)
        for define in DUV.define:
            set_of_change_define_interest.add(define)
        for missing_def in DUV.missing_define:
            set_of_define_interest.add(missing_def)
            temp_client_func.body.block_items.insert(0,
                c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                           bitsize=None,
                           type=c_ast.TypeDecl(declname=missing_def, quals=[],
                                               type=c_ast.IdentifierType(get_type(missing_def)))))
        func_object.node = temp_client_func


    if func != func_object.lib_node:
        func = func_object.lib_node
        if not isinstance(func, c_ast.FuncDef):
            DUV = DUVisitor()
            DUV.visit(func)
            new_func = copy.deepcopy(client_template)

            new_func.decl.name = client_template.decl.name
            renamed_type = new_func.decl.type
            template_type = client_template.decl.type
            while not isinstance(template_type, c_ast.TypeDecl):
                renamed_type = renamed_type.type
                template_type = template_type.type
            renamed_type.declname = template_type.declname
            new_func.decl.type.args = c_ast.ParamList([])
            new_func.body.block_items = []
            new_func.body.block_items.append(copy.deepcopy(func))
            for missing_def in DUV.missing_define:
                new_func.decl.type.args.params.append(
                    c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                               bitsize=None,
                               type=c_ast.TypeDecl(declname=missing_def, quals=[],
                                                   type=c_ast.IdentifierType(get_type(missing_def)))))

                if missing_def in DUV.value_changed:
                    new_func.body.block_items.append(c_ast.Return(c_ast.ID(missing_def)))

            func_object.lib_node = new_func
        elif func_object.arg_lib is not None:
            func_object.lib_node = func
        else:
            func_object.lib_node = new_func

    if func_object.arg_lib is not None:
        func = func_object.arg_lib
        if not isinstance(func, c_ast.FuncDef):
            DUV = DUVisitor()
            DUV.visit(func)
            new_func = copy.deepcopy(client_template)

            new_func.decl.name = client_template.decl.name
            renamed_type = new_func.decl.type
            template_type = client_template.decl.type
            while not isinstance(template_type, c_ast.TypeDecl):
                renamed_type = renamed_type.type
                template_type = template_type.type
            renamed_type.declname = template_type.declname
            new_func.decl.type.args = c_ast.ParamList([])
            new_func.body.block_items = []
            if isinstance(func, c_ast.Compound):
                new_func.body.block_items = copy.deepcopy(func).block_items
            else:
                new_func.body.block_items.append(copy.deepcopy(func))
            for missing_def in DUV.missing_define:
                new_func.decl.type.args.params.append(
                    c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                               bitsize=None,
                               type=c_ast.TypeDecl(declname=missing_def, quals=[],
                                                   type=c_ast.IdentifierType(get_type(missing_def)))))

                if missing_def in DUV.value_changed:
                    new_func.body.block_items.append(c_ast.Return(c_ast.ID(missing_def)))

            for defintion in DUV.define:
                if defintion not in DUV.missing_define and ((defintion+"_old" in set_of_define_interest or defintion+"_new" in set_of_define_interest or
                defintion in set_of_define_interest) or (defintion in DUV.value_changed and (defintion+"_old" in set_of_change_define_interest) or
                                                         (defintion+"_new" in set_of_change_define_interest))):
                    new_func.body.block_items.append(c_ast.Return(c_ast.ID(defintion)))

            func_object.arg_lib = new_func
        else:
            func_object.arg_lib = func


    return func_object








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


class IDhunter(c_ast.NodeVisitor):
    def __init__(self):
        self.container = set()

    def visit_ID(self, node):
        if isinstance(node, c_ast.ID):
            self.container.add(node.name)

    def visit_FuncCall(self, node):
        self.visit(node.args)


class ClientFUnctionHierarchyVisitor(c_ast.NodeVisitor):
    def __init__(self, lib_name, client):
        self.lib_name = lib_name
        self.client = client
        self.parent_child = {}
        self.node_dict = {}
        self.leaves = []
        self.root = None

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """

        for c in node:
            self.parent_child[c] = node
            self.visit(c)


    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            if isinstance(node.name, c_ast.ID):
                if node.name.name == self.lib_name:
                    l_object = self.node_dict.get(node, None)
                    if l_object is None:
                        l_object, _ = self.create_ClientContextNode(node, node, None, node, None)
                        self.node_dict[node] = l_object
                    self.leaves.append(l_object)
                    leaf = set([l_object])
                    c_node = node
                    child_node = node
                    while c_node is not None:
                        pure_loop_check = isinstance(c_node, c_ast.While) or isinstance(c_node,
                                                                                        c_ast.For)
                        loop_type_check = pure_loop_check or isinstance(c_node, c_ast.DoWhile)
                        if loop_type_check or c_node == self.client:
                            c_object = self.node_dict.get(c_node, None)
                            if (c_object is None):
                                if (loop_type_check):
                                    if (isinstance(c_node, c_ast.While)):
                                        child_node_with_loop_context = c_ast.If(cond=c_node.cond, iftrue=child_node, iffalse=None)
                                        c_object, leaf = self.create_ClientContextNode(child_node_with_loop_context, c_node, None, c_node,
                                                                                 l_object, leaf)
                                    elif isinstance(c_node, c_ast.For):
                                        child_node_with_loop_context = c_ast.If(cond=c_node.cond, iftrue=child_node,
                                                                                iffalse=None)
                                        child_node_with_loop_context_complete = c_ast.Compound(block_items=[c_node.init,child_node_with_loop_context ])
                                        c_object, leaf = self.create_ClientContextNode(child_node_with_loop_context_complete, c_node,
                                                                                 None, c_node,
                                                                                 l_object,  leaf)
                                    else:
                                        c_object, leaf = self.create_ClientContextNode(child_node, c_node, None, c_node, l_object, leaf)
                                else:
                                    c_object, leaf = self.create_ClientContextNode(c_node, copy.deepcopy(c_node), None, c_node, l_object, leaf)
                                self.node_dict[c_node]=c_object
                            self.add_parent_child(c_object, l_object)
                            l_object = c_object

                        elif isinstance(c_node, c_ast.Compound ) and not isinstance(child_node, c_ast.FuncDef):
                            child_loc = c_node.block_items.index(child_node)
                            pre_loop, post_loop = self.compute_loop_usage_block(c_node, child_loc)
                            if len(pre_loop) > len(post_loop):
                                max_len = len(pre_loop)
                            else:
                                max_len = len(post_loop)
                            if max_len > 0:
                                for i in range(max_len):
                                    if i < len(pre_loop):
                                        pre_index = pre_loop[i] + 1
                                    else:
                                        pre_index = 0

                                    if i < len(post_loop):
                                        post_index = post_loop[i]
                                    else:
                                        post_index = len(c_node.block_items)

                                    raw_l_object = l_object
                                    context = c_ast.Compound(
                                        block_items=copy.deepcopy(c_node.block_items[pre_index: post_index]))
                                    c_object, leaf = self.create_ClientContextNode(context, copy.deepcopy(context), None, copy.deepcopy(context),
                                                                             raw_l_object, leaf)
                                    self.add_parent_child(c_object, l_object)
                                    l_object = c_object


                        child_node = c_node
                        c_node = self.parent_child.get(c_node, None)

                    self.root = c_object

    def compute_loop_usage_block(self, node, child_index):
        if isinstance(node, c_ast.Compound):
            pre_loop = []
            post_loop = []
            for index in range(child_index+1, len(node.block_items)):
                block = node.block_items[index]
                LPH = LooplHunter()
                LPH.visit(block)
                if LPH.use_loop:
                    post_loop.append(index)

            for index in range(child_index-1, -1, -1):
                block = node.block_items[index]
                LPH = LooplHunter()
                LPH.visit(block)
                if LPH.use_loop:
                    pre_loop.append(index)

            return pre_loop, post_loop






    def add_parent_child(self, parent, child):
        parent.children.append(child)
        child.parent = parent
        if parent.arg_lib is not None:
            child.lib_node = parent.arg_lib


    def create_ClientContextNode(self, node, lib_node, parent, raw_lib_node, known_child=None ,leaf=None):
        global  is_MLCCheker
        hook_installed = False
        should_remove = False
        node_copy = copy.deepcopy(node)
        start, end, arg_lib, arg_client, new_leaf  = self.merge_libs_calls(node)
        if leaf is not None and len(new_leaf) > 0:
            leaf = leaf.union(new_leaf)
        if arg_client is not None and arg_lib is not None:
            node = arg_client
            hook_installed = True
        elif (known_child is not None and known_child.raw_lib_node is not None):
            known_child_content = known_child.raw_lib_node
            child_parent = self.parent_child.get(known_child_content, None)
            if child_parent is not None and isinstance(child_parent, c_ast.Compound):
                index = child_parent.block_items.index(known_child_content)
                #child_parent = copy.deepcopy(child_parent)
                child_parent.block_items[index] = c_ast.Compound(block_items=[c_ast.FuncCall(name=c_ast.ID(name="CLEVER_DELETE"), args=c_ast.ParamList(params =[])), known_child_content])
                hook_installed = True
                should_remove = True

        result = complete_functions(ClientContextDag(copy.deepcopy(node),node_copy, copy.deepcopy(lib_node), parent, raw_lib_node, arg_lib, leaf =leaf), self.client, self.lib_name, is_MLCCheker=is_MLCCheker)
        if (hook_installed):
            CUV = CleanUpVisitor()
            CUV.visit(result.node)
            if should_remove:
                child_parent.block_items.pop(index)
        return result, leaf

    def merge_libs_calls(self, node):
        start = -1
        end = -1
        argumented_client = None
        argumented_lib = None
        LibCV = LibCallHunter(self.lib_name)
        if isinstance(node, c_ast.If):
            if isinstance(node.iftrue, c_ast.Compound):
                checking_blocks = node.iftrue.block_items
        elif isinstance(node, c_ast.FuncDef):
            checking_blocks = node.body.block_items
        elif isinstance(node, c_ast.Compound):
            checking_blocks = node.block_items
        else:
            checking_blocks = []

        new_leaf = set()
        mulitiple_call = False
        for index in range(len(checking_blocks)):
            LibCV.use_lib = False
            block = checking_blocks[index]
            LibCV.visit(block)
            if LibCV.use_lib:
                for lib in LibCV.lib_node:
                    l_object = self.node_dict.get(lib, None)
                    if l_object is  None:
                        l_object, _ = self.create_ClientContextNode(lib, lib, None, lib, None)
                        self.node_dict[node] = l_object
                    new_leaf.add(l_object)

                if (start == -1):
                    start = index
                if (end < index):
                    end =index
                if (len(LibCV.lib_node)> 1):
                    mulitiple_call = True

        if (end > start) or (start == end and mulitiple_call):
            argumented_lib = c_ast.Compound(block_items=checking_blocks[start:end+1])
            argumented_client = copy.deepcopy(node)
            if isinstance(argumented_client, c_ast.If):
                if isinstance(argumented_client.iftrue, c_ast.Compound):
                    blocks = argumented_client.iftrue.block_items
                    argumented_client.iftrue.block_items = blocks[:start] +[c_ast.FuncCall(name=c_ast.ID(name="CLEVER_DELETE"), args=None)]  + blocks[end+1:]
            elif isinstance(argumented_client, c_ast.FuncDef):
                blocks = argumented_client.body.block_items
                argumented_client.body.block_items = blocks[:start] + [c_ast.Compound(block_items=
                    [c_ast.FuncCall(name=c_ast.ID(name="CLEVER_DELETE"), args=None)] + checking_blocks[start:end+1])] + blocks[end+1:]

        return start, end, argumented_lib, argumented_client, new_leaf



class LibCallHunter(c_ast.NodeVisitor):

    def __init__(self, lib_name):
        self.use_lib = False
        self.lib_node =[]
        self.lib_name = lib_name


    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            if node.name.name == self.lib_name:
                self.use_lib = True
                self.lib_node.append(node)
            self.visit(node.args)


class LooplHunter(c_ast.NodeVisitor):

    def __init__(self):
        self.use_loop = False


    def visit_For(self, node):
        if isinstance(node, c_ast.For):
            self.use_loop = True

    def visit_While(self, node):
        if isinstance(node, c_ast.While):
            self.use_loop = True

    def visit_DoWhile(self, node):
        if isinstance(node, c_ast.DoWhile):
            self.use_loop = True



class CleanUpVisitor(c_ast.NodeVisitor):

    def __init__(self):
        self.parent_child = {}

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        for c in node:
            self.parent_child[c] = node
            self.visit(c)

    def visit_FuncCall(self,node):
        if isinstance(node, c_ast.FuncCall):
            if (node.name.name == "CLEVER_DELETE"):
                parent = self.parent_child.get(node, None)
                if parent is not None and isinstance(parent, c_ast.Compound):
                    parent.block_items=[c_ast.FuncCall(name=c_ast.ID(name="lib_old"), args=None), c_ast.FuncCall(name=c_ast.ID(name="lib_new"), args=None)]
                    #grandparent = self.parent_child.get(parent, None)
                    #if grandparent is not None and isinstance(grandparent, c_ast.Compound):
                        #parent_index = grandparent.block_items.index(parent)
                        #grandparent.block_items = grandparent.block_items[0:parent_index] + parent.block_items + grandparent.block_items[parent_index+1:]






class ClientContextDag(object):
    def __init__(self, node, raw_node, lib_node,  parent, raw_lib_node, arg_lib = None, leaf=set()):
        self.node = node
        self.raw_node = raw_node
        self.lib_node = lib_node
        self.raw_lib_node = raw_lib_node
        self.parent = parent
        self.children = []
        self.checked = False
        self.processed = False
        self.eqiv = False
        self.arg_lib = arg_lib
        self.leaf = leaf

    def verify_checked(self):
        self.checked = True
        for child in self.children:
            child.verify_checked()

    def check_leaves(self):
        for l in self.leaf:
            if not l.eqiv:
                return False
        return True

    def mark_leaves(self):
        for l in self.leaf:
            l.eqiv = True