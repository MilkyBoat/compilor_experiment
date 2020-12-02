#ifndef TREE_H
#define TREE_H

#include "pch.h"
#include "type.h"

enum NodeType
{
	NODE_OP,
	NODE_BOOL,
	NODE_CONST, 
	NODE_VAR,
	NODE_TYPE,

	NODE_PROG,
	NODE_STMT,
	NODE_EXPR,
	NODE_VARLIST,
	NODE_PARAM,
};

enum OperatorType
{
	OP_EQ,  	// ==
	OP_NEQ, 	// !=
	OP_GRAEQ,	// >=
	OP_LESEQ,	// <=
	OP_ADDASSIGN,	// +=
	OP_SUBASSIGN,	// -=
	OP_MULASSIGN,	// *=
	OP_DIVASSIGN,	// /=
	OP_ASSIGN,	// =
	OP_GRA,		// >
	OP_LES,		// <
	OP_INC,		// ++
	OP_DEC,		// --
	OP_ADD,		// +
	OP_SUB,		// -
	OP_POS,		// + (一元运算符)
	OP_NAG,		// - (一元运算符)
	OP_MUL,		// *
	OP_DIV,		// /
	OP_MOD,		// %
	OP_NOT,		// !
	OP_AND, 	// &&
	OP_OR,		// ||
	OP_INDEX,	// [] 下标运算符
};

enum StmtType {
	STMT_SKIP,
	STMT_BLOCK,
	STMT_DECL,
	STMT_CONSTDECL,
	STMT_FUNCALL,
	STMT_IFELSE,
	STMT_IF,
	STMT_WHILE,
	STMT_FOR,
	STMT_RETURN,
	STMT_CONTINUE,
	STMT_BREAK,
};

struct TreeNode {
public:
	int nodeID;
	int lineno;
	NodeType nodeType;

	TreeNode* child = nullptr;
	TreeNode* sibling = nullptr;

	TreeNode(int lineno, NodeType type);
	TreeNode(TreeNode* node);	// 仅用于叶节点拷贝，函数不复制子节点，也不复制子节点指针
	void addChild(TreeNode*);
	void addSibling(TreeNode*);

	void printNodeInfo();
	void printChildrenId();

	void printAST();	// 先输出自己 + 孩子们的id；再依次让每个孩子输出AST。
	void printSpecialInfo();
	void printConstVal();

	void genNodeId();

public:
	OperatorType optype;
	StmtType stype;		// 如果是表达式
	Type* type;			// 变量、类型、表达式结点，有类型。
	int int_val;
	char ch_val;
	bool b_val;
	string str_val;
	string var_name;
	string var_scope;	// 变量作用域标识符
    int pointLevel;
	
public:
	static string nodeType2String (NodeType type);
	static string opType2String (OperatorType type);
	static string sType2String (StmtType type);
};

static TreeNode* nodeScanf = new TreeNode(0, NODE_VAR);
static TreeNode* nodePrintf = new TreeNode(0, NODE_VAR);

#endif