#ifndef TREE_H
#define TREE_H

#include "pch.h"
#include "type.h"

enum NodeType
{
	NODE_BOOL,
	NODE_CONST, 
	NODE_VAR,
	NODE_EXPR,
	NODE_TYPE,

	NODE_STMT,
	NODE_PROG,
	
	NODE_OP,
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
	OP_ADD,		// +
	OP_SUB,		// -
	OP_MUL,		// *
	OP_DIV,		// /
	OP_MOD,		// %
	OP_NOT,		// !
	OP_AND, 	// &&
	OP_OR,		// ||
};

enum StmtType {
	STMT_SKIP,
	STMT_DECL,
	STMT_IF,
	STMT_WHILE,
	STMT_FOR,
	STMT_RETURN,
	STMT_CONTINUE,
	STMT_BREAK,
};

struct TreeNode {
public:
	int nodeID;  // 用于作业的序号输出
	int lineno;
	NodeType nodeType;

	TreeNode* child = nullptr;
	TreeNode* sibling = nullptr;

	void addChild(TreeNode*);
	void addSibling(TreeNode*);

	void printNodeInfo();
	void printChildrenId();

	void printAST(); // 先输出自己 + 孩子们的id；再依次让每个孩子输出AST。
	void printSpecialInfo();

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
	int var_scope;		// 变量作用域标识符
	
public:
	static string nodeType2String (NodeType type);
	static string opType2String (OperatorType type);
	static string sType2String (StmtType type);

public:
	TreeNode(int lineno, NodeType type);
};

#endif