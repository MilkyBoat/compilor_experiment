#include "tree.h"
using namespace std;

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

TreeNode::TreeNode(int lineno, NodeType type) {
    this->lineno = lineno;
    this->nodeType = type;
}

void TreeNode::genNodeId() {
    
}

void TreeNode::printNodeInfo() {

}

void TreeNode::printChildrenId() {

}

void TreeNode::printAST() {
    printNodeInfo();
    printChildrenId();
    TreeNode* p = this->child;
    while (p != nullptr) {
        p->printAST();
        p = p->sibling;
    }
}

// You can output more info...
void TreeNode::printSpecialInfo() {
    switch(this->nodeType){
        case NODE_CONST:
            break;
        case NODE_VAR:
            break;
        case NODE_EXPR:
            break;
        case NODE_STMT:
            break;
        case NODE_TYPE:
            break;
        default:
            break;
    }
}

string TreeNode::sType2String(StmtType type) {
    switch (type)
    {
    case STMT_SKIP:
        return "skip";
    case STMT_DECL:
        return "decl";
    default:
        return "?";
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
        return "<expresion>";
    case NODE_TYPE:
        return "<type>";
    case NODE_STMT:
        return "<statment>";
    case NODE_PROG:
        return "<program>";
    case NODE_OP:
        return "<operation>";
    default:
        return "<?>";
    }
}
