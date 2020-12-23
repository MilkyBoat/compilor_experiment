%option nounput
%{
#include "common.h"
#include "main.tab.h"  // yacc header

int lineno = 1;

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
"{" return LBRACE;
"}" return RBRACE;
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
"if" return IF_;
"else" return ELSE;
"while" return WHILE_;
"for" return FOR_;
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
 *			IF
 *			WHILE
 *			FOR
 *			funcLPAREN
 *		pop:
 *			ifStmt(代码段尾部)
 *			whileStmt(代码段尾部)
 *			forStmt(代码段尾部)
 *			funcDef(代码段尾部)
 */
