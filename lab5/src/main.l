%option nounput
%{
#include "common.h"
#include "main.tab.h"  // yacc header

int lineno = 1;

// max_scope_id 是堆栈下一层结点的最大编号
unsigned char max_scope_id = SCOPT_ID_BASE;
string presentScope = "1";
unsigned int top = 0;

// multimap <标识符名称， 作用域> 变量名列表
multimap<string, string> idNameList = {
    {"scanf", "1"},
    {"printf", "1"}
};
// map <<标识符名称， 作用域>, 结点指针> 变量列表
map<pair<string, string>, TreeNode*> idList = {
    {make_pair("scanf", "1"), nodeScanf},
    {make_pair("printf", "1"), nodePrintf}
};

/*
 *	作用域比较函数 int scopeCmp (string, string)
 *
 *  输入参数： 
 *    presScope： 当前变量所处的作用域
 *    varScope:   希望进行比较的已声明变量作用域
 *
 *  返回值：
 *    0： 作用域相同，
 *          若为变量声明语句，为变量重定义。
 *   >0： 已声明变量作用域在当前作用域外层，返回作用域距离（堆栈层数）
 *          若为声明语句，不产生冲突，当前变量为新定义变量，
 *          若为使用语句，当前变量为新定义变量。
 *   -1：已声明变量作用域在当前作用域内层，
 *          若为声明语句，不可能出现这种情况，
 *          若为使用语句，不产生冲突。
 *   -2：两个作用域互不包含，任何情况下都不会互相干扰
 */
int scopeCmp(string presScope, string varScope) {
	unsigned int plen = presScope.length(), vlen = varScope.length();
	unsigned int minlen = min(plen, vlen);
	if (presScope.substr(0, minlen) == varScope.substr(0, minlen)) {
		if (plen >= vlen)
			return plen - vlen;
		else
			return -1;
	}
	return -2;
}

void scopePush() {
	presentScope += max_scope_id;
	max_scope_id = SCOPT_ID_BASE;
	top++;
#ifdef SCOPE_DEBUG
	cout << "* push -> " << presentScope << ", at line " << lineno << endl;
#endif
}

void scopePop() {
	max_scope_id = presentScope[top] + 1;
	presentScope = presentScope.substr(0, presentScope.length() - 1);
	top--;
#ifdef SCOPE_DEBUG
	cout << "* pop -> " << presentScope << ", at line " << lineno << endl;
#endif
}

%}

BLOCKCOMMENT_BEGIN "/*"
BLOCKCOMMENT_ELE .
BLOCKCOMMENT_LINE \n
BLOCKCOMMENT_END "*/"
%x BLOCKCOMMENT
LINECOMMENT \/\/[^\n]*
EOL	(\r\n|\r|\n)
WHILTESPACE [[:blank:]]

OCTINT 0[0-7]+
DECINT -?[0-9]+
HEXINT 0[Xx][0-9a-fA-F]+

BOOL (true)|(false)
STRING \"[^(\")]*\"
CHAR \'.?\'

IDENTIFIER [[:alpha:]_][[:alpha:][:digit:]_]*

%%

{BLOCKCOMMENT_BEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{BLOCKCOMMENT_ELE} {}
<BLOCKCOMMENT>{BLOCKCOMMENT_LINE} {lineno++;}
<BLOCKCOMMENT>{BLOCKCOMMENT_END} {BEGIN INITIAL;}
{LINECOMMENT}  {}

"int" return T_INT;
"bool" return T_BOOL;
"char" return T_CHAR;
"void" return T_VOID;

"&" return ADDR;

"(" return LPAREN;
")" return RPAREN;
"[" return LBRACKET;
"]" return RBRACKET;
"{" {scopePush(); return LBRACE;}
"}" {scopePop(); return RBRACE;}
"," return COMMA;
";" return SEMICOLON;

"==" return EQ;
">=" return GRAEQ;
"<=" return LESEQ;
"!=" return NEQ;
"=" return ASSIGN;
"+=" return PLUSASSIGN;
"-=" return MINUSASSIGN;
"*=" return MULASSIGN;
"/=" return DIVASSIGN;
"++" return INC;
"--" return DEC;
">" return GRA;
"<" return LES;
"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
"%" return MOD;
"&&" return AND;
"||" return OR;
"!" return NOT;

"const" return CONST;
"if" {scopePush(); return IF;}
"else" return ELSE;
"while" {scopePush(); return WHILE;}
"for" {scopePush(); return FOR;}
"break" return BREAK;
"continue" return CONTINUE;
"return" return RETURN;

"printf" {
    nodePrintf->var_name = "printf";
    nodePrintf->var_scope = "1";
    yylval = nodePrintf;
    return IDENTIFIER;
};
"scanf" {
    nodeScanf->var_name = "scanf";
    nodeScanf->var_scope = "1";
    yylval = nodeScanf;
    return IDENTIFIER;
};

{BOOL} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_BOOL;
    node->b_val = strcmp("false", yytext);
    yylval = node;
    return BOOL;
}

{OCTINT} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_INT;
    node->int_val = strtol(yytext, NULL, 8);
    yylval = node;
    return INTEGER;
}

{DECINT} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_INT;
    node->int_val = atoi(yytext);
    yylval = node;
    return INTEGER;
}

{HEXINT} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_INT;
    node->int_val = strtol(yytext, NULL, 16);
    yylval = node;
    return INTEGER;
}

{CHAR} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_CHAR;
    node->ch_val = yytext[1];
    yylval = node;
    return CHAR;
}

{STRING} {
    TreeNode* node = new TreeNode(lineno, NODE_CONST);
    node->type = TYPE_STRING;
    string text = yytext;
    node->str_val = text.substr(1, text.length()-2);
    yylval = node;
    return STRING;
}

{IDENTIFIER} {
    TreeNode* node = new TreeNode(lineno, NODE_VAR);
    node->var_name = string(yytext);
    yylval = node;
#ifdef ID_TOKEN_DEBUG
    cout << "% get IDENTIFIER :" << yytext <<endl;
#endif
    return IDENTIFIER;
}

{WHILTESPACE} {}

{EOL} {lineno++;}

. {
    cerr << "[line "<< lineno <<" ] unknown character:" << yytext << endl;
}
%%

/*
 *	变量作用域切换只会发生在以下地方：
 *
 *		函数体		type funcName ( params ) block
 *								  ↑ push		  ↑ pop
 *
 *		block块		{ stmts }
 *					↑ push	↑ pop
 *
 *		if语句		IF ( cond ) block
 *					↑ push			  ↑ pop
 *
 *					IF ( cond ) block ELSE block
 *					↑ push						 ↑ pop
 *
 *		while语句	WHILE ( cond ) block
 *					↑ push				 ↑ pop
 *
 *		for语句		FOR ( expr ; cond ; expr ) block
 *					↑ push							 ↑ pop
 *
 *					FOR ( decl ; cond ; expr ) block
 *					↑ push							 ↑ pop
 *
 * 	可得作用域推进表：
 *
 *		push:
 *			{
 *			IF
 *			WHILE
 *			FOR
 *			funcLPAREN
 *		pop:
 *			}
 *			ifStmt(代码段尾部)
 *			whileStmt(代码段尾部)
 *			forStmt(代码段尾部)
 *			funcDef(代码段尾部)
 */
