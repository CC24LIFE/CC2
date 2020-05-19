from pycparser import c_ast, c_generator
import copy
is_MLCCheker = True


type_dict={}

def record_type_dict(types):
    global  type_dict
    type_dict = types


def analyze_client(client_node, lib, parent=None, void_ret = False):
    CFV = ClientFUnctionHierarchyVisitor (lib, client_node, parent = parent, void_ret =void_ret)
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

def get_def_type_from_struct(missing_def, struct):
    '''
    for candidate in struct.decls:
        if candidate.name == missing_def:
            return candidate.type
        elif isinstance(candidate.type, c_ast.Struct):
            type = get_def_type_from_struct(missing_def, candidate.type)
            if type is not None:
                return type
    '''
    return None



def get_def_type(missing_def, usage_node_object, vistor):
    type_map = usage_node_object.type_map
    ret_val  = type_map.get(missing_def, None)
    if ret_val is not None:
        return ret_val
    child_node = usage_node_object.tree_node
    parent_node = vistor.parent_child.get(child_node, None)
    while parent_node is not None:
        if isinstance(parent_node, c_ast.FileAST):
            for candidate_node in parent_node.ext:
                if isinstance(candidate_node, c_ast.Decl):
                    if candidate_node.name == missing_def:
                        ret_val = candidate_node.type
                        break
                    elif isinstance(candidate_node.type, c_ast.Struct):
                        type = get_def_type_from_struct(missing_def, candidate_node.type)
                        if (type is not None):
                            ret_val = type
                            break
            if ret_val is None:
                child_node = parent_node
                parent_node = vistor.parent_child.get(child_node, None)
                continue
            else:
                copy_ob = copy.deepcopy(ret_val)
                type_map[missing_def] = copy_ob
                return copy_ob
        if isinstance(parent_node, c_ast.FuncDef):
            if parent_node.decl.type.args is not None:
                candidates = parent_node.decl.type.args.params
                for candidate_node in candidates:
                    if candidate_node.name == missing_def:
                        ret_val = candidate_node.type
                        copy_ob = copy.deepcopy(ret_val)
                        type_map[missing_def] = copy_ob
                        return copy_ob
            child_node = parent_node
            parent_node = vistor.parent_child.get(child_node, None)
        elif isinstance(parent_node, c_ast.Compound):
            for candidate_node in parent_node.block_items:
                if candidate_node == child_node:
                    break
                elif isinstance(candidate_node, c_ast.Decl):
                    if candidate_node.name == missing_def:
                        ret_val = candidate_node.type

            if ret_val is None:
                child_node = parent_node
                parent_node = vistor.parent_child.get(child_node, None)
                continue
            else:
                copy_ob = copy.deepcopy(ret_val)
                type_map[missing_def] = copy_ob
                return copy_ob
        else:
            child_node = parent_node
            parent_node = vistor.parent_child.get(child_node, None)
            continue
    if ret_val is None:
        print(missing_def)
        return



'''
Given a fragment of C functions, complete the function by adding approipate input variables
'''
def complete_functions(func_object, client_template, lib, vistor, is_MLCCheker =True):
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
                def_type = get_def_type(missing_def, func_object, vistor)
                new_func.decl.type.args.params.append(
                    c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                               bitsize=None,
                               type=def_type))

                if missing_def in DUV.value_changed:
                    new_func.body.block_items.append(c_ast.Return(c_ast.ID(missing_def)))
        else:
            new_func = func

        func_object.raw_node = new_func

    func = func_object.node
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
    if isinstance(func, c_ast.FuncDef):
        new_func.body = copy.deepcopy(func.body)
        new_func.decl.type.args = copy.deepcopy(func.decl.type.args)
    else:
        new_func.body.block_items.append(copy.deepcopy(func))
    return_statement = []
    count = 0
    for missing_def in DUV.missing_define:
        def_type= get_def_type(missing_def, func_object, vistor)
        if def_type is None:
            continue
        new_func.decl.type.args.params.append(
                                            c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                                                       bitsize=None,
                                                       type = def_type))

        if missing_def in DUV.value_changed:
            #return_statement.append(c_ast.Return(c_ast.ID(missing_def)))
            return_statement.append(c_ast.FuncCall(name=c_ast.ID(name="_RETTYPE"),args=c_ast.ExprList(exprs=[c_ast.ID(missing_def), c_ast.Constant(type='int', value=str(count))])))
            count+=1
    #if func is a just a program segment, then also add local variables
    if isinstance(func, c_ast.Compound):
        for value_changed in DUV.value_changed:
            if value_changed not in DUV.missing_define:
                #return_statement.append(c_ast.Return(c_ast.ID(value_changed)))
                return_statement.append(c_ast.FuncCall(name=c_ast.ID(name="_RETTYPE"), args=c_ast.ExprList(
                    exprs=[c_ast.ID(value_changed), c_ast.Constant(type='int', value=str(count))])))
                count+=1
    return_statement.append(c_ast.FuncCall(name=c_ast.ID(name="END"), args=None))
    JPV = JumpVisitor()
    JPV.visit_and_work(new_func, return_statement)
    new_func.body.block_items = new_func.body.block_items + return_statement

    #func_object.node = checker.version_merge_client(new_func, lib)
    func_object.node = new_func
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
            def_type = get_def_type(missing_def, func_object, vistor)
            set_of_define_interest.add(missing_def)
            temp_client_func.body.block_items.insert(0,
                c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                           bitsize=None,
                           type=def_type))
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
            return_statement = []
            for missing_def in DUV.missing_define:
                def_type = get_def_type(missing_def, func_object, vistor)
                if def_type is None:
                    continue
                new_func.decl.type.args.params.append(
                    c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                               bitsize=None,
                               type=def_type))

                if missing_def in DUV.value_changed:
                    return_statement.append(c_ast.Return(c_ast.ID(missing_def)))

            JPV = JumpVisitor()
            JPV.visit_and_work(new_func, return_statement)
            new_func.body.block_items = new_func.body.block_items + return_statement

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
                def_type = get_def_type(missing_def, func_object, vistor)
                new_func.decl.type.args.params.append(
                    c_ast.Decl(name=missing_def, quals=[], storage=[], init=None, funcspec=[],
                               bitsize=None,
                               type=def_type))

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


class Label_Searcher(c_ast.NodeVisitor):
    def __init__(self, target_label):
        self.target_label = target_label
        self.search_result = False

    def visit_Label(self, node):
        if isinstance(node, c_ast.Label):
            if (node.name == self.target_label):
                self.search_result = True
            else:
                self.generic_visit(node)


class JumpVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.parent_child ={}
        self.target_location = []
        self.root = None

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """

        for c in node:
            self.parent_child[c] = node
            self.visit(c)

    def is_local_jump(self, node):
        child_node = node
        parent_node = self.parent_child.get(child_node, None)
        while parent_node is not None and not isinstance(parent_node, c_ast.FuncDef):
            if isinstance(parent_node, c_ast.For) or isinstance(parent_node, c_ast.While) or isinstance(parent_node, c_ast.DoWhile):
                return True
            else:
                child_node = parent_node
                parent_node = self.parent_child.get(child_node, None)
        return False

    def is_local_goto(self, node):
        goto_label = node.name
        LS = Label_Searcher(goto_label)
        LS.visit(self.root)
        return LS.search_result


    def visit_Continue(self, node):
        if isinstance(node, c_ast.Continue) and not self.is_local_jump(node):
            parent_node = self.parent_child[node]
            self.target_location.append((parent_node, node))

    def visit_Break(self, node):
        if isinstance(node, c_ast.Break) and not self.is_local_jump(node):
            parent_node = self.parent_child[node]
            self.target_location.append((parent_node, node))

    def visit_Goto(self, node):
        if isinstance(node, c_ast.Goto) and not self.is_local_goto(node):
            parent_node = self.parent_child[node]
            self.target_location.append((parent_node, node))

    def visit_Return(self, node) :
        if isinstance(node, c_ast.Return):
            parent_node = self.parent_child[node]
            self.target_location.append((parent_node, node))


    def work(self, new_stuffs):
        for parent, child in self.target_location:
            if isinstance(child, c_ast.Return):
                new_stuffs_copy = new_stuffs[:-1] + [c_ast.FuncCall(name=c_ast.ID(name="_RETTYPE"), args=c_ast.ExprList(
                    exprs=[child.expr, c_ast.Constant(type='int', value=str(len(new_stuffs)-1))]))] + new_stuffs[-1:]
            else:
                new_stuffs_copy = new_stuffs
            if isinstance(parent, c_ast.Compound):
                child_loc = parent.block_items.index(child)
                parent.block_items = parent.block_items[:child_loc] + new_stuffs_copy + parent.block_items[child_loc+1:]
            elif isinstance(parent, c_ast.If):
                if parent.iftrue == child:
                    parent.iftrue = c_ast.Compound(block_items=new_stuffs_copy)
                elif parent.iffalse == child:
                    parent.iffalse = c_ast.Compound(block_items=new_stuffs_copy)
            elif isinstance(parent, c_ast.While):
                parent.stmt = c_ast.Compound(block_items=new_stuffs_copy)
            elif isinstance(parent, c_ast.For):
                parent.stmt = c_ast.Compound(block_items=new_stuffs_copy)
            elif isinstance(parent, c_ast.DoWhile):
                parent.stmt = c_ast.Compound(block_items=new_stuffs_copy)
            elif isinstance(parent, c_ast.Label):
                parent.stmt = c_ast.Compound(block_items=new_stuffs_copy)

    def visit_and_work(self, node, new_stuffs):
        self.parent_child = {}
        self.target_location = []
        self.root = node
        self.visit(node)
        self.work(new_stuffs)
        self.root= None

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
        if node.args is not None:
            self.visit(node.args)

class Label_Finder(c_ast.NodeVisitor):
    def __init__(self, verified):
        self.link_dict = {}
        self.verified = verified

    def visit_Label(self, node):
        if isinstance(node, c_ast.Label):
            label_name = node.name
            result = self.link_dict.get(label_name, None)
            if result is None:
                self.link_dict[label_name] = []
            #FIXME alter point for infinite loop
            self.generic_visit(node)

    def visit(self, node):
        if node in self.verified.keys():
            values = self.verified.get(node)
            for value in values:
                self.link_dict[value]=[]
        else:
            super().visit(node)

class GOTO_finder(c_ast.NodeVisitor):
    def __init__(self, target, link_dict ):
        self.target = target
        self.link_dict = link_dict

    def visit_Goto(self, node):
        if isinstance(node, c_ast.Goto):
            label_name = node.name
            if label_name in self.link_dict.keys():
                self.link_dict[label_name].append(node)

    def visit(self, node):
        if (node != self.target):
            super().visit(node)



class ClientFUnctionHierarchyVisitor(c_ast.NodeVisitor):
    def __init__(self, lib_name, client, parent=None, void_ret = False):
        self.lib_name = lib_name
        self.void_ret = void_ret
        self.client = client
        self.parent_child = {}
        self.node_dict = {}
        self.leaves = []
        self.root = None
        if (parent is not None):
            self.parent_child[client] = parent

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """

        for c in node:
            self.parent_child[c] = node
            self.visit(c)

    def check_loop_localness(self, node, verified):
        LBF = Label_Finder(verified)
        LBF.visit(node)
        GTF = GOTO_finder(node,LBF.link_dict)
        GTF.visit(self.client)
        result = True
        verified.clear()
        verified[node] = []
        for key, item in GTF.link_dict.items():
            if len(item) > 0:
                result = False
                verified[node].append(key)
        return result

    def visit_FuncCall(self, node):
        og_node = node
        if isinstance(node, c_ast.FuncCall):
            if isinstance(node.name, c_ast.ID):
                if node.name.name == self.lib_name:
                    l_object = self.node_dict.get(node, None)
                    if l_object is None:
                        if (self.void_ret):
                            l_object, _ = self.create_ClientContextNode(node,
                                                                        node, None, node, None)
                        else:
                            l_object, _ = self.create_ClientContextNode(c_ast.Return(expr=node), c_ast.Return(expr=node), None, node, None)
                        l_object.type_map[c_generator.CGenerator().visit(node)] = "LIB-TYPE"
                        self.node_dict[node] = l_object
                        self.leaves.append(l_object)
                    leaf = set([l_object])
                    c_node = node
                    child_node = node
                    verified = dict()
                    while c_node is not None:
                        pure_loop_check = (isinstance(c_node, c_ast.While) or isinstance(c_node,
                                                                                        c_ast.For)) \
                                          and self.check_loop_localness(c_node, verified)
                        loop_type_check = pure_loop_check or isinstance(c_node, c_ast.DoWhile)
                        if loop_type_check or c_node == self.client:
                            c_object = self.node_dict.get(c_node, None)
                            if (c_object is None):
                                if (loop_type_check):
                                    if (isinstance(c_node, c_ast.While)):
                                        child_node_with_loop_context = c_ast.If(cond=c_node.cond, iftrue=child_node, iffalse=None)
                                        self.parent_child[child_node_with_loop_context] = c_node
                                        c_object, leaf = self.create_ClientContextNode(child_node_with_loop_context, c_node, None, c_node,
                                                                                 l_object, leaf)
                                    elif isinstance(c_node, c_ast.For):
                                        child_node_with_loop_context = c_ast.If(cond=c_node.cond, iftrue=child_node,
                                                                                iffalse=None)
                                        child_node_with_loop_context_complete = c_ast.Compound(block_items=[child_node_with_loop_context ])
                                        if c_node.init is not None:
                                            child_node_with_loop_context_complete.block_items = [c_node.init] + child_node_with_loop_context_complete.block_items
                                        self.parent_child[child_node_with_loop_context_complete] = c_node
                                        c_object, leaf = self.create_ClientContextNode(child_node_with_loop_context_complete, c_node,
                                                                                 None, c_node,
                                                                                 l_object,  leaf)
                                    else:
                                        c_object, leaf = self.create_ClientContextNode(child_node, c_node, None, c_node, l_object, leaf)
                                else:
                                    c_object, leaf = self.create_ClientContextNode(c_node, copy.deepcopy(c_node), None, c_node, l_object, leaf, treeNode=og_node)
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
                                    context_raw = c_ast.Compound(
                                        block_items=c_node.block_items[pre_index: post_index])
                                    context = c_ast.Compound(
                                        block_items=copy.deepcopy(c_node.block_items[pre_index: post_index]))
                                    self.parent_child[context] = c_node
                                    c_object, leaf = self.create_ClientContextNode(context, copy.deepcopy(context), None, copy.deepcopy(context),
                                                                             raw_l_object, leaf, merge_parent=c_node, treeNode=context, raw_context = context_raw)
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


    def create_ClientContextNode(self, node, lib_node, parent, raw_lib_node, known_child=None ,leaf=None, treeNode = None, simple=True, merge_parent =None, raw_context =None):
        global  is_MLCCheker
        hook_installed = False
        should_remove = False
        node_copy = copy.deepcopy(node)
        if raw_context is None:
            start, end, arg_lib, arg_client, new_leaf  = self.merge_libs_calls(node, merge_parent = merge_parent)
        else:
            start, end, arg_lib, arg_client, new_leaf = self.merge_libs_calls(raw_context, merge_parent=merge_parent)
        if leaf is not None and len(new_leaf) > 0:
            leaf = leaf.union(new_leaf)
        if arg_client is not None and arg_lib is not None:
            node = arg_client
            hook_installed = True
        elif (known_child is not None and known_child.raw_lib_node is not None):
            known_child_content = known_child.raw_lib_node
            child_parent = self.parent_child.get(known_child_content, None)
            if child_parent is not None and isinstance(child_parent, c_ast.Compound):
                if not simple:
                    index = child_parent.block_items.index(known_child_content)
                    child_parent = copy.deepcopy(child_parent)
                    child_parent.block_items[index] = c_ast.Compound(block_items=[c_ast.FuncCall(name=c_ast.ID(name="CLEVER_DELETE"), args=c_ast.ParamList(params =[])), known_child_content])
                    hook_installed = True
                    should_remove = True

        if leaf is None:
            leaf = set()
        result = complete_functions(ClientContextDag(copy.deepcopy(node),node_copy, copy.deepcopy(lib_node), parent, raw_lib_node, arg_lib, leaf =leaf, tree_Node=treeNode), self.client, self.lib_name, self, is_MLCCheker=is_MLCCheker)
        if (hook_installed):
            CUV = CleanUpVisitor()
            CUV.visit(result.node)
            if should_remove:
                child_parent.block_items.pop(index)
        return result, leaf

    def merge_libs_calls(self, node, simple = True, merge_parent = None):
        start = -1
        end = -1
        argumented_client = None
        argumented_lib = None
        LibCV = LibCallHunter(self.lib_name)
        if isinstance(node, c_ast.If):
            if isinstance(node.iftrue, c_ast.Compound):
                checking_blocks = node.iftrue.block_items
                block_parent = node.iftrue
        elif isinstance(node, c_ast.FuncDef):
            checking_blocks = node.body.block_items
            block_parent = node.body
        elif isinstance(node, c_ast.Compound):
            checking_blocks = node.block_items
            block_parent = node
        else:
            checking_blocks = []
            block_parent = None

        new_leaf = set()
        mulitiple_call = False
        for index in range(len(checking_blocks)):
            LibCV.use_lib = False
            block = checking_blocks[index]
            if merge_parent is not None:
                self.parent_child[block] = merge_parent
            else:
                self.parent_child[block] = block_parent
            LibCV.visit(block)
            self.parent_child = dict(list(self.parent_child.items()) + list(LibCV.parent_child.items()))
            if LibCV.use_lib:
                for lib in LibCV.lib_node:
                    l_object = self.node_dict.get(lib, None)
                    if l_object is None:
                        if self.void_ret:
                            l_object, _ = self.create_ClientContextNode(lib, lib,
                                                                        None, lib, None, treeNode=lib)
                        else:
                            l_object, _ = self.create_ClientContextNode(c_ast.Return(expr= lib), c_ast.Return(expr= lib), None, lib, None, treeNode=lib)
                        l_object.type_map[c_generator.CGenerator().visit(lib)] = "LIB-TYPE"
                        self.node_dict[lib] = l_object
                        self.leaves.append(l_object)
                    new_leaf.add(l_object)

                if (start == -1):
                    start = index
                if (end < index):
                    end =index
                if (len(LibCV.lib_node)> 1):
                    mulitiple_call = True

        if not simple and ((end > start) or (start == end and mulitiple_call)):
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
        self.parent_child = {}

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        for c in node:
            self.parent_child[c] = node
            self.visit(c)


    def visit_FuncCall(self, node):
        if isinstance(node, c_ast.FuncCall):
            if node.name.name == self.lib_name:
                self.use_lib = True
                self.lib_node.append(node)
            if node.args is not None:
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
    def __init__(self, node, raw_node, lib_node,  parent, raw_lib_node, arg_lib = None, leaf=set(), tree_Node = None):
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
        self.type_map = dict()
        if tree_Node is not None:
            self.tree_node = tree_Node
        else:
            self.tree_node = self.raw_lib_node

    def verify_checked(self):
        self.checked = True
        for child in self.children:
            child.verify_checked()

    def check_leaves(self):
        if len(self.leaf) == 0:
            return False
        for l in self.leaf:
            if not l.eqiv:
                return False
        return True

    def mark_leaves(self):
        for l in self.leaf:
            l.eqiv = True