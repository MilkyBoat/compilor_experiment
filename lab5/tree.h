#include <string>
using namespace std;
enum NodeType
{
	NODE_BOOL,
	NODE_CONST,
	NODE_VAR,
	NODE_STMT,
	NODE_PROG,
	NODE_OP,
	NODE_TYPE
};
enum OpType
{
	OP_EQUAL,
	OP_ADD,
	OP_NOT
};
enum StatType
{
	STMT_ASSIGN,
	STMT_DECL,
	STMT_IF,
	STMT_WHILE,
	STMT_SCANF,
	STMT_PRINTF
};
enum VarType
{
	VAR_VOID,
	VAR_INTEGER
};
struct TreeNode
{
	NodeType nodeType;	//结点类型
	OpType opType;		//操作符具体类型 结点是操作符时写入具体类型
	
	//在构造结点时直接填入类型
	TreeNode(NodeType type) {

	}

	void addChild(TreeNode*& child) {

	}

	void addSibling(TreeNode*& sib) {

	}

	void genNodeId() {

	}

	void printAST() {

	}

	StatType stmtType;
	VarType varType;
	string var_name;
	bool bool_val;
	int int_val;
};
