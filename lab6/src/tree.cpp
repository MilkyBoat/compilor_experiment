#include "tree.h"

// -------------------------------------------------------------
// ------------------------- 常量字符串 -------------------------
// -------------------------------------------------------------

string _ident = "\"LuczyCompiler: (Ubuntu 1.0.0ubuntu1~18.04) 1.0.0\"";
string _section = ".note.GNU-stack,\"\",@progbits";

// --------------------------------------------------------------
// --------------------- 工具函数 重载运算符 ----------------------
// --------------------------------------------------------------

string operator + (string &content, int number) {
    return content + to_string(number);
}

string& operator += (string &content, int number) {
	return content = content + to_string(number);
}

// ------------------------------------------------------------
// ----------------------- 全局变量 ----------------------------
// ------------------------------------------------------------

// multimap <标识符名称， 作用域> 变量名列表
multimap<string, string> idNameList;
// map <<标识符名称， 作用域>, 结点指针> 变量列表
map<pair<string, string>, TreeNode *> idList;

// map <字符串， 标签序列号> 字符串表
map<string, int> strList;

// map <作用域+变量名， 变量相对于ebp偏移量> 局部变量表，在每次函数定义前清空
// <"11a", "-12"> 表示第一个函数的栈上第一个分配的局部变量（前3个4字节为bx,cx,dx备份用，始终保留）
map<string, int> LocalVarList;
// 栈上为局部变量分配的空间总大小，在return时进行清理
int stackSize;

// 当前所处函数的声明结点指针，return使用
TreeNode *pFunction;

// 循环体栈，为continue与break配对使用
TreeNode *cycleStack[10];
int cycleStackTop = -1;

// ------------------------------------------------------------
// ------------------------ 代码 ------------------------------
// ------------------------------------------------------------

TreeNode::TreeNode(int lineno, NodeType type) {
    this->lineno = lineno;
    this->nodeType = type;
    this->pointLevel = 0;
}

TreeNode::TreeNode(TreeNode* node) {
    this->lineno = node->lineno;
    this->nodeType = node->nodeType;
    this->optype = node->optype;
	this->stype = node->stype;
	this->type = node->type;
	this->int_val = node->int_val;
	this->ch_val = node->ch_val;
	this->b_val = node->b_val;
	this->str_val = node->str_val;
	this->var_name = node->var_name;
	this->var_scope = node->var_scope;
    this->pointLevel = node->pointLevel;
}

void TreeNode::addChild(TreeNode* child) {
    if (this->child == nullptr) {
        this->child = child;
    }
    else {
        this->child->addSibling(child);
    }
}

void TreeNode::addSibling(TreeNode* sibling) {
    TreeNode* p = this;
    while (p->sibling != nullptr) {
        p = p->sibling;
    }
    p->sibling = sibling;
}

int TreeNode::getChildNum() {
    int num = 0;
    for (TreeNode *p = child; p != nullptr; p = p->sibling)
        num++;
    return num;
}

int TreeNode::getVal() {
    if (nodeType == NODE_CONST) {
        switch (type->type)
        {
        case VALUE_BOOL:
            return (b_val ? 1 : 0);
        case VALUE_CHAR:
            return (int)ch_val;
        case VALUE_INT:
            return int_val;
        default:
            return 0;
        }
    }
    else if (child->nodeType == NODE_CONST) {
        return child->getVal();
    }
    return 0;
}

void TreeNode::genNodeId() {
    static unsigned int maxid = 0;
    this->nodeID = maxid++;
    if (this->child)
        this->child->genNodeId();
    if (this->sibling)
        this->sibling->genNodeId();
}

void TreeNode::typeCheck() {

#ifdef typeCheck_debug
            cout << "# Type check reach @" << nodeID << endl;
#endif

    // 类型检查时记录循环层数，为continue和break提供循环外错误检查
    if (nodeType == NODE_STMT && (stype == STMT_FOR || stype == STMT_WHILE)) {
        cycleStackTop++;
    }

    // 先遍历子节点进行type计算
    TreeNode *p = this->child;
    while (p != nullptr) {
        p->typeCheck();
        p = p->sibling;
    }

#ifdef typeCheck_debug
            cout << "# Type check start @" << nodeID << endl;
#endif

    // 分情况检查类型错误并对部分情况作强制类型转换
    switch (this->nodeType)
    {
    case NODE_FUNCALL:
        // 函数调用要求标识符是一个函数，且形参表与函数定义一致
        if (child->type->type == COMPOSE_FUNCTION) {
            if (child->var_name == "printf" || child->var_name == "scanf") {
                if (child->sibling->child->type->type != VALUE_STRING) {
                    cout << "Wrong type: paramater type doesn`t fit function " << child->var_name
                         << "need <string>, got " << child->sibling->child->type->getTypeInfo()
                         << " , at line " << lineno << endl;
                    typeError = true;
                }
                break;
            }
            if (child->sibling->getChildNum() == child->type->paramNum) {
                int paracnt = 0;
                TreeNode *param = child->sibling->child;
                while (param!=nullptr) {
                    if (child->type->paramType[paracnt] != TYPE_NONE // 无类型表示支持任意类型，在scanf和printf上使用
                        && child->type->paramType[paracnt]->type != param->type->type) {
                        cout << "Wrong type: paramater type doesn`t fit function " << child->var_name
                                << " got " << param->type->getTypeInfo()
                                << " need " << child->type->paramType[paracnt]->getTypeInfo()
                                << ", at line " << lineno << endl;
                        typeError = true;
                    }
                    paracnt++;
                    param = param->sibling;
                }
            }
            else {
                cout << "Wrong type: paramater num doesn`t fit function " << child->var_name << " , at line " << lineno << endl;
                typeError = true;
            }
        }
        else {
            cout << "Wrong type: identifier " << child->var_name << " isn`t a function, at line " << lineno << endl;
            typeError = true;
        }
        if (!type)
            this->type = new Type(NOTYPE);
        this->type->copy(child->type->retType);
        break;
    case NODE_STMT:
        // statement无类型
        this->type = TYPE_NONE;
        switch (stype) {
        case STMT_FUNCDECL: {
            vector<TreeNode *> retList;
            findReturn(retList);
            int size = retList.size();
            if (child->sibling->type->retType->type == VALUE_VOID) {
                // void类型函数无return或return无子节点
                for (int i = 0; i < size; i++) {
                    if (retList[i]->child) {
                        cout << "Wrong return: none void return in void function, at line " << retList[i]->lineno << endl;
                        typeError = true;
                    }
                }
            }
            else {
                // 其它函数必须return且类型一致
                if (size == 0) {
                    cout << "Wrong return: none void function without any return statement, function decl at line " << child->sibling->lineno << endl;
                    typeError = true;
                }
                else {
                    for (int i = 0; i < size; i++) {
                        if (retList[i]->child) {
                            if (retList[i]->child->type->type != child->type->type) {
                                cout << "Wrong type: return type can`t fit function return type, at line " 
                                << retList[i]->lineno << endl;
                            typeError = true;
                            }
                        }
                        else {
                            cout << "Wrong return: return nothing in none void function, at line " << retList[i]->lineno << endl;
                            typeError = true;
                        }
                    }
                }
            }
            break;
        }
        case STMT_IF:
        case STMT_IFELSE:
        case STMT_WHILE:
            if (child->type->type != VALUE_BOOL) {
                if (child->type->type == VALUE_INT) {
                    // 强制类型转换，添加一个"!=0"运算过程
                    TreeNode *eq = new TreeNode(child->lineno, NODE_OP);
                    eq->sibling = child->sibling;
                    eq->child = child;
                    eq->type = TYPE_BOOL;
                    eq->optype = OP_NEQ;
                    child->sibling = new TreeNode(child->lineno, NODE_CONST);
                    child->sibling->type = TYPE_INT;
                    child->sibling->int_val = 0;
                    child = eq;
                    cout << "# Type Cast from <int> to <bool> because of a \""
                         << this->sType2String(stype)
                         << "\" statement, at line " << child->lineno << endl;
                }
                else {
                    cout << "Wrong type: need <bool>, got " << child->type->getTypeInfo()
                         << ", at line " << child->lineno << endl;
                    typeError = true;
                }
            }
            if (stype == STMT_WHILE)
                cycleStackTop--;
            break;
        case STMT_FOR:
            if (child->sibling->type->type != VALUE_BOOL) {
                if (child->sibling->type->type == VALUE_INT) {
                    cout << "# Type Cast from <int> to <bool> because of a \"for\" statement, at line "
                         << child->sibling->lineno << endl;
                }
                else {
                    cout << "Wrong type: need <bool>, got " << child->sibling->type->getTypeInfo()
                         << ", at line " << child->sibling->lineno << endl;
                    typeError = true;
                }
            }
            if (stype == STMT_FOR)
                cycleStackTop--;
            break;
        case STMT_BREAK:
        case STMT_CONTINUE:
            if (cycleStackTop < 0) {
                cout << "Error cycle control statement: " << sType2String(stype)
                     << ", outside a cycle, at line " << lineno << endl;
                typeError = true;
            }
            break;
        case STMT_RETURN:

            break;
        default:
            break;
        }
        break;
    case NODE_EXPR:
        this->type = this->child->type;
        this->pointLevel = this->child->pointLevel;
        break;
    case NODE_OP:
        if (optype == OP_INC || optype == OP_DEC || optype == OP_POS || optype == OP_NAG) {
            // 一元运算符，输入int，输出int，++,--,+(一元),-(一元)
            if (this->child->type->type != VALUE_INT) {
                cout << "Wrong type: need <int>, got <" << child->type->getTypeInfo()
                     << ">, operator is " << opType2String(optype) << ", at line " << lineno << endl;
                typeError = true;
            }
            this->type = TYPE_INT;
        } 
        else if (optype == OP_EQ || optype == OP_NEQ || optype == OP_ASSIGN || optype == OP_DECLASSIGN) {
            // 二元运算符，输入无限制，两侧同类型，==,!=,=
            // ！！！不要在指针声明时候初始化！！！
            if (this->child->type->type != this->child->sibling->type->type) {
                cout << "Wrong type: type in two sides of " << opType2String(optype)
                     << " operator mismatched, got <" << child->type->getTypeInfo()
                     << "> and <" << child->sibling->type->getTypeInfo()
                     << ">, at line " << lineno << endl;
                typeError = true;
            }
            if (optype == OP_ASSIGN && child->type->constvar) {
                cout << "Wrong assign: assign to a const varable, at line " << lineno;
                typeError = true;
            }
            if (optype == OP_ASSIGN || optype == OP_DECLASSIGN)
                this->type = this->child->type;
            else
                this->type = TYPE_BOOL;
        }
        else if (optype == OP_GRA || optype == OP_LES || optype == OP_GRAEQ || optype == OP_LESEQ) {
            // 二元运算符，输入int，输出bool，>,<,>=,<=
            if (this->child->type->type != this->child->sibling->type->type || this->child->type->type != VALUE_INT) {
                cout << "Wrong type: need <int>, got <" << child->type->getTypeInfo()
                     << "> and <" << child->sibling->type->getTypeInfo()
                     << ">, operator is " << opType2String(optype) << ", at line " << lineno << endl;
                typeError = true;
            }
            this->type = TYPE_BOOL;
        }
        else if (optype == OP_ADDASSIGN || optype == OP_SUBASSIGN || optype == OP_MULASSIGN || optype == OP_DIVASSIGN) {
            // 二元运算符，输入int，输出int，+=,-=,*=,/=
            if (this->child->type->type != this->child->sibling->type->type || this->child->type->type != VALUE_INT) {
                cout << "Wrong type: need <int>, got <" << child->type->getTypeInfo()
                     << "> and <" << child->sibling->type->getTypeInfo()
                     << ">, operator is " << opType2String(optype) << ", at line " << lineno << endl;
                typeError = true;
            } 
            else if (child->type->constvar) {
                cout << "Wrong assign: assign to a const varable, at line " << lineno;
                typeError = true;
            }
            this->type = TYPE_INT;
        }
        else if (optype == OP_NOT || optype == OP_AND || optype == OP_OR) {
            // 二元运算符，输入bool，输出bool，!,&&,||
            if (this->child->type->type != VALUE_BOOL 
                || (optype != OP_NOT 
                && this->child->type->type != this->child->sibling->type->type)) {
                cout << "Wrong type: need <bool>, got <" << child->type->getTypeInfo()
                     << "> and <" << child->sibling->type->getTypeInfo()
                     << ">, operator is " << opType2String(optype) << ", at line " << lineno << endl;
                typeError = true;
            }
            this->type = TYPE_BOOL;
        }
        else if (optype == OP_INDEX) {
            // 二元运算符，输入int，输出左值类型，[]下标运算符
            if (this->child->sibling->type->type != VALUE_INT) {
                cout << "Wrong type: need <int>, got <" << child->sibling->type->getTypeInfo()
                     << ">, operator is " << opType2String(optype) << ", at line " << lineno << endl;
                typeError = true;
            }
            this->type = this->child->type;
        }
        else {
            // 二元运算符，输入int，输出int，+,-,*,/,%
            if (this->child->type->type != this->child->sibling->type->type || this->child->type->type != VALUE_INT) {
                cout << "Wrong type: need <int>, got <" << child->type->getTypeInfo()
                     << "> and <" << child->sibling->type->getTypeInfo()
                     << ">, operator is " << opType2String(optype) << ", at line " << lineno << endl;
                typeError = true;
            }
            this->type = TYPE_INT;
        }
        break;
    case NODE_PROG:
        this->type = TYPE_NONE;
        break;
    case NODE_VARLIST:
    case NODE_PARAM:
        if (this->child)
            this->type = this->child->type;
        break;
    default:
        break;
    }
    
#ifdef typeCheck_debug
            cout << "# Type check end @" << nodeID << endl;
#endif

}

void TreeNode::findReturn(vector<TreeNode *> &retList) {
    if (nodeType == NODE_STMT && stype == STMT_RETURN)
        retList.push_back(this);
    else {
        TreeNode *p = child;
        while (p) {
            p->findReturn(retList);
            p = p->sibling;
        }
    }
}

void TreeNode::genCode() {
    TreeNode *p = child;
    TreeNode **q;
    int N = 0, n = 1, pSize = 0;
    string varCode = "";
    switch (nodeType)
    {
    case NODE_PROG:
        gen_header();
        gen_var_decl();
        gen_str();
        cout << "\t.text" << endl;
        while (p) {
            if (p->nodeType == NODE_STMT && p->stype == STMT_FUNCDECL)
                p->genCode();
            p = p->sibling;
        }
        cout << "\t.ident\t" << _ident << endl
             << "\t.section " << _section << endl;
        break;
    case NODE_FUNCALL:
        // 反转链表
        N = p->sibling->getChildNum();
#ifdef childNumdebug
        cout << "# ChildNum = " << N << endl;
#endif
        q = new TreeNode *[N];
        p = p->sibling->child;
        while (p) {
            q[N - n++] = p;
            p = p->sibling;
        }
        // 从右向左压栈
        for (int i = 0; i < N; i++) {
            q[i]->genCode();
            cout << "\tpushl\t%eax" << endl;
            pSize += this->child->type->paramType[i]->getSize();
        }
        // call和参数栈清理
        cout << "\tcall\t" << child->var_name << endl
             << "\taddl\t$" << pSize << ", %esp" << endl;
        break;
    case NODE_STMT:
        switch (stype)
        {
        case STMT_FUNCDECL:
            cycleStackTop = -1;
            pFunction = this;
            get_label();
            cout << "\t.globl\t" << p->sibling->var_name << endl
                 << "\t.type\t" << p->sibling->var_name << ", @function" << endl
                 << p->sibling->var_name << ":" << endl;
            gen_var_decl();
            cout << "\tpushl\t%ebp" << endl
                 << "\tmovl\t%esp, %ebp" << endl;
            // 在栈上分配局部变量
            cout << "\tsubl\t$" << -stackSize << ", %esp" << endl;
            // 内部代码递归生成
            p->sibling->sibling->sibling->genCode();
            // 产生返回标签代码
            cout << this->label.next_label << ":" << endl;
            // 清理局部变量栈空间
            cout << "\taddl\t$" << -stackSize << ", %esp" << endl;
            cout << "\tpopl\t%ebp" << endl
                 << "\tret" << endl;
            pFunction = nullptr;
            break;
        case STMT_DECL:
        case STMT_CONSTDECL:
            p = p->sibling->child;
            while (p) {
                if (p->nodeType == NODE_OP) {
                    p->child->sibling->genCode();
                    // 这里也很蠢，可以通过三地址码优化一下
                    cout << "\tmovl\t%eax, " << LocalVarList[p->child->var_scope + p->child->var_name] << "(%ebp)" << endl;
                }
                p = p->sibling;
            }
            break;
        case STMT_IF:
            get_label();
            cout << label.begin_label << ":" << endl;
            this->child->genCode();
            cout << label.true_label << ":" << endl;
            this->child->sibling->genCode();
            cout << label.false_label << ":" << endl;
            break;
        case STMT_IFELSE:
            get_label();
            cout << label.begin_label << ":" << endl;
            this->child->genCode();
            cout << label.true_label << ":" << endl;
            this->child->sibling->genCode();
            cout << "\tjmp\t\t" << label.next_label << endl;
            cout << label.false_label << ":" << endl;
            this->child->sibling->sibling->genCode();
            cout << label.next_label << ":" << endl;
            break;
        case STMT_WHILE:
            get_label();
            cycleStack[++cycleStackTop] = this;
            cout << label.next_label << ":" << endl;
            this->child->genCode();
            cout << label.true_label << ":" << endl;
            this->child->sibling->genCode();
            cout << "\tjmp\t\t" << label.next_label << endl;
            cout << label.false_label << ":" << endl;
            cycleStackTop--;
            break;
        case STMT_FOR:
            get_label();
            cycleStack[++cycleStackTop] = this;
            this->child->genCode();
            cout << label.begin_label << ":" << endl;
            this->child->sibling->genCode();
            cout << label.true_label << ":" << endl;
            this->child->sibling->sibling->sibling->genCode();
            cout << label.next_label << ":" << endl;
            this->child->sibling->sibling->genCode();
            cout << "\tjmp\t\t" << label.begin_label << endl;
            cout << label.false_label << ":" << endl; 
            cycleStackTop--;
            break;
        case STMT_BREAK:
            cout << "\tjmp\t\t" << cycleStack[cycleStackTop]->label.false_label << endl;
            break;
        case STMT_CONTINUE:
            cout << "\tjmp\t\t" << cycleStack[cycleStackTop]->label.next_label << endl;
            break;
        case STMT_RETURN:
            if (p) {
                p->genCode();
            }
            cout << "\tjmp\t\t" << pFunction->label.next_label << endl;
            break;
        case STMT_BLOCK:
            while (p) {
                p->genCode();
                p = p->sibling;
            }
            break;
        default:
            break;
        }
        break;
    case NODE_EXPR:
        if (child->nodeType == NODE_VAR) {
            // 内存变量（全局/局部）
            string varCode = getVarNameCode(this->child);
            if (child->pointLevel == 0)
                cout << "\tmovl\t" << varCode << ", %eax" << endl;
            else if (child->pointLevel < 0) { // &前缀的变量
                cout << "\tleal\t" << varCode << ", %eax" << endl;
            }
            else {
                cout << "\tmovl\t" << varCode << ", %eax" << endl;
                for (int i = 0; i < child->pointLevel; i++) {
                    cout << "\tmovl\t(%eax), %eax" << endl;
                }
            }
        }
        else if (child->nodeType == NODE_OP && child->optype == OP_INDEX) {
            // 数组
            child->genCode();
        }
        else {
            // 立即数、常量字符串
            if (child->type->type == VALUE_STRING) {
                cout << "\tmovl\t$.LC" << strList[child->str_val] << ", %eax" << endl;
            }
            else {
                cout << "\tmovl\t$" << child->getVal() << ", %eax" << endl;
            }
        }
        break;
    case NODE_OP:
        switch (optype)
        {
        case OP_EQ:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tcmpl\t%eax, %ebx" << endl
                 << "\tsete\t%al" << endl;
            if (label.true_label != "") {
                cout << "\tje\t\t" << label.true_label << endl
                     << "\tjmp\t\t" << label.false_label << endl;
            }
            break;
        case OP_NEQ:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tcmpl\t%eax, %ebx" << endl
                 << "\tsetne\t%al" << endl;
            if (label.true_label != "") {
                cout << "\tjne\t\t" << label.true_label << endl
                     << "\tjmp\t\t" << label.false_label << endl;
            }
            break;
        case OP_GRA:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tcmpl\t%eax, %ebx" << endl
                 << "\tsetg\t%al" << endl;
            if (label.true_label != "") {
                cout << "\tjg\t\t" << label.true_label << endl
                     << "\tjmp\t\t" << label.false_label << endl;
            }
            break;
        case OP_LES:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tcmpl\t%eax, %ebx" << endl
                 << "\tsetl\t%al" << endl;
            if (label.true_label != "") {
                cout << "\tjl\t\t" << label.true_label << endl
                     << "\tjmp\t\t" << label.false_label << endl;
            }
            break;
        case OP_GRAEQ:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tcmpl\t%eax, %ebx" << endl
                 << "\tsetge\t%al" << endl;
            if (label.true_label != "") {
                cout << "\tjge\t\t" << label.true_label << endl
                     << "\tjmp\t\t" << label.false_label << endl;
            }
            break;
        case OP_LESEQ:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tcmpl\t%eax, %ebx" << endl
                 << "\tsetle\t%al" << endl;
            if (label.true_label != "") {
                cout << "\tjle\t\t" << label.true_label << endl
                     << "\tjmp\t\t" << label.false_label << endl;
            }
            break;
        case OP_NOT:
            get_label();
            p->genCode();
            // cout << "\tandl\t%eax, $eax" << endl
            //      << "\tsete\t%al" << endl;
            break;
        case OP_AND:
            get_label();
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            cout << child->label.true_label << ":" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\tandl\t%eax, %ebx" << endl
                 << "\tsetne\t%al" << endl;
            break;
        case OP_OR:
            get_label();
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            cout << child->label.false_label << ":" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl
                 << "\torb\t%al, %bl" << endl
                 << "\tsetne\t%al" << endl;
            break;
        case OP_ADDASSIGN:
            varCode = getVarNameCode(p);
            p->sibling->genCode();
            
            cout << "\tmovl\t" << varCode << ", %ebx" << endl
                 << "\taddl\t%ebx, %eax" << endl
                 << "\tmovl\t%eax, " << varCode << endl;
            break;
        case OP_SUBASSIGN:
            varCode = getVarNameCode(p);
            p->sibling->genCode();
            cout << "\tmovl\t" << varCode << ", %ebx" << endl
                 << "\tsubl\t%eax, %ebx" << endl
                 << "\tmovl\t%ebx, %eax" << endl
                 << "\tmovl\t%eax, " << varCode << endl;
            break;
        case OP_MULASSIGN:
            varCode = getVarNameCode(p);
            p->sibling->genCode();
            cout << "\tmovl\t" << varCode << ", %ebx" << endl
                 << "\timull\t%ebx, %eax" << endl
                 << "\tmovl\t%eax, " << varCode << endl;
            break;
        case OP_DIVASSIGN:
            varCode = getVarNameCode(p);
            p->sibling->genCode();
            cout << "\tmovl\t%eax, %ebx" << varCode << endl
                 << "\tmovl\t" << varCode << ", %eax" << endl
                 << "\tcltd" << endl
                 << "\tidivl\t%ebx" << endl
                 << "\tmovl\t%eax, " << varCode << endl;
            break;
        case OP_DECLASSIGN:
        case OP_ASSIGN:
            p->sibling->genCode();
            if (p->nodeType == NODE_VAR)
                cout << "\tmovl\t%eax, " << getVarNameCode(p) << endl;
            else {  // 左值是数组
                cout << "\tpushl\t%eax" << endl;
                // 计算偏移量到%eax
                p->child->sibling->genCode();
                cout << "\tpopl\t%ebx" << endl
                     << "\tmovl\t%ebx, " << getVarNameCode(p) << endl;
            }
            break;
        case OP_INC:
            varCode = getVarNameCode(p);
            cout << "\tmovl\t" << varCode << ", %eax" << endl
                 << "\tincl\t" << varCode << endl;
            break;
        case OP_DEC:
            varCode = getVarNameCode(p);
            cout << "\tmovl\t" << varCode << ", %eax" << endl
                 << "\tdecl\t" << varCode << endl;
            break;
        case OP_ADD:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl;
            cout << "\taddl\t%ebx, %eax" << endl;
            break;
        case OP_SUB:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tmovl\t%eax, %ebx" << endl
                 << "\tpopl\t%eax" << endl
                 << "\tsubl\t%ebx, %eax" << endl;
            break;
        case OP_POS:
            p->genCode();
            break;
        case OP_NAG:
            p->genCode();
            cout << "\tnegl\t%eax" << endl;
            break;
        case OP_MUL:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tpopl\t%ebx" << endl;
            cout << "\timull\t%ebx, %eax" << endl;
            break;
        case OP_DIV:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tmovl\t%eax, %ebx" << endl
                 << "\tpopl\t%eax" << endl
                 << "\tcltd" << endl
                 << "\tidivl\t%ebx" << endl;
            break;
        case OP_MOD:
            p->genCode();
            cout << "\tpushl\t%eax" << endl;
            p->sibling->genCode();
            cout << "\tmovl\t%eax, %ebx" << endl
                 << "\tpopl\t%eax" << endl
                 << "\tcltd" << endl
                 << "\tidivl\t%ebx" << endl
                 << "\tmovl\t%edx, %eax" << endl;
            break;
        case OP_INDEX:
            // 这里只生成下标运算在右值时的代码（即按下标取数值）
            p->sibling->genCode();
            cout << "\tmovl\t" << getVarNameCode(this) << ", %eax" << endl;
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void TreeNode::gen_header() {
	cout << "# generated by xuyunkai`s SysY compiler." << endl;
}

void TreeNode::gen_var_decl() {
    if (nodeType == NODE_PROG) {
        // 根节点下只处理全局变量声明
        TreeNode *p = child;
        bool print_data = false;
        while(p) {
            // 发现了p为定义语句，LeftChild为类型，RightChild为声明表
            if (p->stype == STMT_DECL || p->stype == STMT_CONSTDECL) {
                TreeNode* q = p->child->sibling->child;
                // q为变量表语句，可能为标识符或者赋值声明运算符
                while (q) {
                    if (!print_data) {
                        // 第一次遇到全局变量的时候输出
                        print_data = true;
                        cout << "\t.text" << endl
                            << "\t.data" << endl
                            << "\t.align\t4" << endl;
                    }
                    TreeNode *t = q;
                    if (q->nodeType == NODE_OP && q->optype == OP_DECLASSIGN) {
                        t = q->child;
                    }
                    // 遍历常变量列表，指针类型视为4字节int
                    int varsize = ((t->type->pointLevel == 0) ? t->type->getSize() : 4);
                    if (t->type->dim > 0) {
                        t->type->elementType = p->child->type->type;
                        t->type->type = VALUE_ARRAY;
                        varsize = t->type->getSize();
                    }
                    cout << "\t.globl\t" << t->var_name << endl
                         << "\t.type\t" << t->var_name << ", @object" << endl
                         << "\t.size\t" << t->var_name << ", " << varsize << endl
                         << t->var_name << ":" << endl;
                    if (q->nodeType == NODE_OP && q->optype == OP_DECLASSIGN) {
                        // 声明时赋值
                        // 只处理字面量初始化值
                        if (t->type->dim == 0) {    // 单个值                    
                            cout << "\t.long\t" << t->sibling->getVal() << endl;
                        }
                        else {    // 数组                    
                            for (TreeNode *pe = t->sibling->child; pe != nullptr; pe = pe->sibling)
                                cout << "\t.long\t" << 4 * pe->getVal() << endl;
                        }
                    }
                    else {
                        // 声明时未赋值，默认初始化值为0
                        // 只处理字面量初始化值
                        if (t->type->dim == 0) { // 单个值
                            cout << "\t.long\t0" << endl;
                        }
                        else {  // 数组
                            int size = 1;
                            for (unsigned int i = 0; i < t->type->dim; i++)
                                size *= t->type->dimSize[i];
                            cout << "\t.zero\t" << size << endl;
                        }
                    }
                    q = q->sibling;
                }
            }
            p = p->sibling;
        }
    }
    else if (nodeType == NODE_STMT && stype == STMT_FUNCDECL) {
        // 对于函数声明语句，递归查找局部变量声明
        LocalVarList.clear();
        stackSize = -12;
        int paramSize = 8;
#ifdef varDeclDebug
        cout << "# gen_var_decl in funcDecl init" << endl;
#endif
        // 遍历参数定义列表
        TreeNode *p = child->sibling->sibling->child;
        while (p) {
            // 只能是基本数据类型，简便起见一律分配4字节
            LocalVarList[p->child->sibling->var_scope + p->child->sibling->var_name] = paramSize;
            paramSize += 4;
            p = p->sibling;
        }
#ifdef varDeclDebug
        cout << "# gen_var_decl in funcDecl param fin" << endl;
#endif
        // 遍历代码段，查找函数内声明的局部变量
        p = child->sibling->sibling->sibling->child;
        while (p) {
            p->gen_var_decl();
            p = p->sibling;
        }
#ifdef varDeclDebug
        cout << "# gen_var_decl in funcDecl fin" << endl;
#endif
    }
    else if (nodeType == NODE_STMT && (stype == STMT_DECL || stype == STMT_CONSTDECL)) {
#ifdef varDeclDebug
        cout << "# gen_var_decl found varDecl stmt at node " << nodeID << endl;
#endif
        // 找到了局部变量定义
        TreeNode* q = child->sibling->child;
        while (q) {
            // 遍历常变量列表，指针类型视为4字节int
            // q为标识符或声明赋值运算符
            TreeNode *t = q;
            // 声明时赋值
            if (q->nodeType == NODE_OP && q->optype == OP_DECLASSIGN)
                t = q->child;
            int varsize = ((t->type->pointLevel == 0) ? t->type->getSize() : 4);
            if (t->type->dim > 0) {
                t->type->type = VALUE_ARRAY;
                varsize = t->type->getSize();
            }
            LocalVarList[t->var_scope + t->var_name] = stackSize;
            stackSize -= varsize;
            q = q->sibling;
        }
    } 
    else {
        // 在函数定义语句块内部递归查找局部变量声明
        TreeNode *p = child;
        while (p) {
            p->gen_var_decl();
            p = p->sibling;
        }
    }
}

void TreeNode::gen_str() {
    static int strseq = 0;
    static bool print_rodata = false;
    TreeNode *p = this->child;
    while (p) {
        if (p->nodeType == NODE_CONST && p->type->type == VALUE_STRING) {
            if (!print_rodata) {
                print_rodata = true;
                cout << "\t.section\t.rodata" << endl;
            }
            if (strList.count(p->str_val) == 0) {
                strList[p->str_val] = strseq;
                cout << ".LC" << strseq++ << ":" << endl
                        << "\t.string\t" << "\"" << p->str_val << "\"" << endl;
            }
        } 
        else if (p->child) {
            p->gen_str();
        }
        p = p->sibling;
    }
}

string TreeNode::new_label() {
    static int label_seq = 0;
    string labelStr = ".L";
    labelStr += label_seq++;
    return labelStr;
}

void TreeNode::get_label() {
    string temp;
    switch (nodeType)
    {
    case NODE_STMT:
        switch (stype)
        {
        case STMT_FUNCDECL:
            this->label.begin_label = this->child->sibling->var_name;
            // next为return和局部变量清理
            this->label.next_label = ".LRET_" + this->child->sibling->var_name;
            break;
        case STMT_IF:
            this->label.begin_label = new_label();
            this->label.true_label = new_label();
            this->label.false_label = this->label.next_label = new_label();
            this->child->label.true_label = this->label.true_label;
            this->child->label.false_label = this->label.false_label;
            break;
        case STMT_IFELSE:
            this->label.begin_label = new_label();
            this->label.true_label = new_label();
            this->label.false_label = new_label();
            this->label.next_label = new_label();
            this->child->label.true_label = this->label.true_label;
            this->child->label.false_label = this->label.false_label;
            break;
        case STMT_WHILE:
            this->label.begin_label = this->label.next_label = new_label();
            this->label.true_label = new_label();
            this->label.false_label = new_label();
            this->child->label.true_label = this->label.true_label;
            this->child->label.false_label = this->label.false_label;
            break;
        case STMT_FOR:
            this->label.begin_label = new_label();
            this->label.true_label = new_label();
            this->label.false_label = new_label();
            this->label.next_label = new_label();
            this->child->sibling->label.true_label = this->label.true_label;
            this->child->sibling->label.false_label = this->label.false_label;
            break;
        default:
            break;
        }
        break;
    case NODE_OP:
        switch (optype)
        {
        case OP_AND:
            child->label.true_label = new_label();
            child->sibling->label.true_label = label.true_label;
            child->label.false_label = child->sibling->label.false_label = label.false_label;
            break;
        case OP_OR:
            child->label.true_label = child->sibling->label.true_label = label.true_label;
            child->label.false_label = new_label();
            child->sibling->label.false_label = label.false_label;
            break;
        case OP_NOT:
            child->label.true_label = label.false_label;
            child->label.false_label = label.true_label;
            break;
        default:
            break;
        }
        break;   
    default:
        break;
    }
}

string TreeNode::getVarNameCode(TreeNode* p) {
    string varCode = "";
    if (p->nodeType == NODE_VAR) {
        // 标识符
        if (p->var_scope == "1") {
            // 全局变量
            varCode = p->var_name;
        }
        else {
            // 局部变量（不要跨定义域访问）
            varCode += LocalVarList[p->var_scope + p->var_name];
            varCode += "(%ebp)";                
        }
    }
    else {
        // 数组
        if (p->child->var_scope == "1") {
            varCode = p->child->var_name + "(,%eax,4)";
        }
        else {
            varCode += LocalVarList[p->child->var_scope + p->child->var_name];
            varCode += "(%ebp,%eax,4)";
        }
    }
    return varCode;
}

void TreeNode::printAST() {
    printNodeInfo();
    printChildrenId();
    cout << endl;
    TreeNode *p = this->child;
    while (p != nullptr) {
        p->printAST();
        p = p->sibling;
    }
}

void TreeNode::printNodeInfo() {
    cout << "# @" << this->nodeID << "\t";
    cout << "line " << lineno << "\t";
    cout << nodeType2String(this->nodeType);
    this->printSpecialInfo();
}

void TreeNode::printChildrenId() {
    cout << ",\tchild:";
    TreeNode *p = this->child;
    if (p == nullptr)
        cout << "-";
    while (p) {
        cout << "\t@" << p->nodeID;
        p = p->sibling;
    }
    cout << "\t";
}

void TreeNode::printSpecialInfo() {
    switch(this->nodeType){
        case NODE_CONST:
            cout << ", ";
            this->printConstVal();
            break;
        case NODE_VAR:
            cout << ",\tname: ";
            if (this->type->pointLevel != 0) {
                // 为指针类型添加前缀(*和&)
                string prefix = this->type->pointLevel > 0 ? "*" : "&";
                for (int i=0; i < abs(this->type->pointLevel); i++)
                    cout << prefix;
            }
            cout << var_name << ",\tscope: ";
            for (unsigned int i = 0; i < var_scope.length(); i++)
                cout << var_scope[i] << " ";
            break;
        case NODE_EXPR:
            break;
        case NODE_STMT:
            cout << ", " << sType2String(this->stype) << "\t";
            if (this->stype == STMT_DECL || this->stype == STMT_CONSTDECL) {
                if (this->child && this->child->sibling && this->child->sibling->type)
                    cout << this->child->sibling->type->getTypeInfo() << "\t";
            }
            break;
        case NODE_TYPE:
            cout << ", " << this->type->getTypeInfo();
            break;
        case NODE_OP:
            cout << ", " << opType2String(this->optype) << "\t";
            break;
        default:
            break;
    }
}

string TreeNode::nodeType2String (NodeType type){
    switch (type)
    {
    case NODE_CONST:
        return "<const>";
    case NODE_VAR:
        return "<var>";
    case NODE_EXPR:
        return "<expression>";
    case NODE_TYPE:
        return "<type>";
    case NODE_FUNCALL:
        return "function call";
    case NODE_STMT:
        return "<statment>";
    case NODE_PROG:
        return "<program>";
    case NODE_VARLIST:
        return "<variable list>";
    case NODE_PARAM:
        return "function format parameter";
    case NODE_OP:
        return "<operation>";
    default:
        return "<?>";
    }
}

string TreeNode::sType2String(StmtType type) {
    switch (type)
    {
    case STMT_SKIP:
        return "skip";
    case STMT_DECL:
        return "declaration";
    case STMT_CONSTDECL:
        return "const declaration";
    case STMT_FUNCDECL:
        return "function declaration";
    case STMT_BLOCK:
        return "block";
    case STMT_IF:
        return "if";
    case STMT_IFELSE:
        return "if with else";
    case STMT_WHILE:
        return "while";
    case STMT_FOR:
        return "for";
    case STMT_RETURN:
        return "return";
    case STMT_CONTINUE:
        return "continue";
    case STMT_BREAK:
        return "break";
    default:
        return "?";
    }
}

string TreeNode::opType2String(OperatorType type) {
    switch (type)
    {
	case OP_EQ:
		return "equal";
	case OP_NEQ:
		return "not equal";
	case OP_GRAEQ:
		return "grater equal";
	case OP_LESEQ:
		return "less equal";
	case OP_ASSIGN:
		return "assign";
	case OP_DECLASSIGN:
		return "assign(decl)";
	case OP_ADDASSIGN:
		return "add assign";
	case OP_SUBASSIGN:
		return "sub assign";
	case OP_MULASSIGN:
		return "multiply assign";
	case OP_DIVASSIGN:
		return "divide assign";
	case OP_GRA:
		return "grater";
	case OP_LES:
		return "less";
    case OP_INC:
        return "auto increment";
    case OP_DEC:
        return "auto decrement";
    case OP_ADD:
        return "add";
	case OP_SUB:
		return "sub";
	case OP_POS:
		return "positive";
	case OP_NAG:
		return "nagative";
	case OP_MUL:
		return "multiply";
	case OP_DIV:
		return "divide";
	case OP_MOD:
		return "Modulo";
	case OP_NOT:
		return "not";
	case OP_AND:
		return "and";
	case OP_OR:
        return "or";
    case OP_INDEX:
        return "index";
    default:
        return "?";
    }
}

void TreeNode::printConstVal() {
    if (this->nodeType == NODE_CONST){
        cout << this->type->getTypeInfo() << ":";
        switch (this->type->type)
        {
        case VALUE_BOOL:
            if (this->b_val)
                cout << "true";
            else
                cout << "fasle";
            break;
        case VALUE_CHAR:
            switch (ch_val)
            {
            case '\n':
                cout << "\\n";
                break;
            case '\r':
                cout << "\\r";
                break;
            case '\t':
                cout << "\\t";
                break;
            case '\0':
                cout << "\\0";
                break;
            default:
                cout << ch_val;
                break;
            }
            break;
        case VALUE_INT:
            cout << int_val;
            break;
        case VALUE_STRING:
            cout << str_val;
            break;
        default:
            cout << "-";
            break;
        }
    }
}

void InitIOFunctionNode() {
    int k = 4;
    nodeScanf->lineno = -1;
    nodeScanf->var_name = "scanf";
    nodeScanf->var_scope = "1";
    nodeScanf->type = new Type(COMPOSE_FUNCTION);
    nodeScanf->type->retType = TYPE_VOID;
    nodeScanf->type->paramType[nodeScanf->type->paramNum++] = TYPE_STRING;
    for (int i = 0; i < k;i++)
        nodeScanf->type->paramType[nodeScanf->type->paramNum++] = TYPE_INT;
    idNameList.insert(make_pair("scanf", "1"));
    idList[make_pair("scanf", "1")] = nodeScanf;
    nodePrintf->lineno = -1;
    nodePrintf->var_name = "printf";
    nodePrintf->var_scope = "1";
    nodePrintf->type = new Type(COMPOSE_FUNCTION);
    nodePrintf->type->retType = TYPE_VOID;
    nodePrintf->type->paramType[nodePrintf->type->paramNum++] = TYPE_STRING;
    for (int i = 0; i < k;i++)
        nodePrintf->type->paramType[nodePrintf->type->paramNum++] = TYPE_INT;
    idNameList.insert(make_pair("printf", "1"));
    idList[make_pair("printf", "1")] = nodePrintf;
}
