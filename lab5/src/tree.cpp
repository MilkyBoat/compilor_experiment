#include "tree.h"
void TreeNode::addChild(TreeNode* child) {

}

void TreeNode::addSibling(TreeNode* sibling){

}

TreeNode::TreeNode(int lineno, NodeType type) {

}

void TreeNode::genNodeId() {

}

void TreeNode::printNodeInfo() {

}

void TreeNode::printChildrenId() {

}

void TreeNode::printAST() {

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
    return "?";
}


string TreeNode::nodeType2String (NodeType type){
    return "<>";
}
