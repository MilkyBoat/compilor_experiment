#include "tree.h"
using namespace std;

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

void TreeNode::addSibling(TreeNode* sibling){
    TreeNode* p = this;
    while (p->sibling != nullptr) {
        p = p->sibling;
    }
    p->sibling = sibling;
}

void TreeNode::genNodeId() {
    static unsigned int maxid = 0;
    this->nodeID = maxid++;
    if (this->child)
        this->child->genNodeId();
    if (this->sibling)
        this->sibling->genNodeId();
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
    cout << "@" << this->nodeID << "\t";
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
            if (this->pointLevel != 0) {
                // 为指针类型添加前缀(*和&)
                string prefix = this->pointLevel > 0 ? "*" : "&";
                for (int i=0; i < abs(this->pointLevel); i++)
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
            if (this->stype == STMT_DECL) {
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
    case NODE_BOOL:
        return "<bool>";
    case NODE_CONST:
        return "<const>";
    case NODE_VAR:
        return "<var>";
    case NODE_EXPR:
        return "<expression>";
    case NODE_TYPE:
        return "<type>";
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
    case STMT_FUNCALL:
        return "function call";
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
            cout << ch_val;
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
