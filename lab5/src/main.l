%option nounput
%{
#include "common.h"
#include "main.tab.h"  // yacc header

int lineno=1;
%}

BLOCKCOMMENT \/\*([^\*^\/]*|[\*^\/*]*|[^\**\/]*)*\*\/
LINECOMMENT \/\/[^\n]*
EOL	(\r\n|\r|\n)
WHILTESPACE [[:blank:]]

CONT "*"
ADDR "&"

LPAREN "("
RPAREN ")"
LBRACE "{"
RBRACE "}"
SEMICOLON ";"

EQ "=="
GRAEQ ">="
LESEQ "<="
NEQ "!="
ASSIGN "="
PLUSASSIGN "+="
MINUSASSIGN "-="
MULASSIGN "*="
DIVASSIGN "/="
GRA ">"
LES "<"
PLUS "+"
MINUS "-"
MUL "*"
DIV "/"
MOD "%"
AND "&&"
OR "||"
NOT "!"

CONST "const"
VOID "void"
IF "if"
ELSE "else"
WHILE "while"
FOR "for"
BREAK "break"
CONTINUE "continue"
RETURN "return"
INT "int"

PRINT "printf"
SCAN "scanf"

OCTINT 0[0-7]+
DECINT -?[0-9]+
HEXINT 0[Xx][0-9a-fA-F]+

CHAR \'.?\'
STRING \"[^(\\")]*\"

IDENTIFIER [[:alpha:]_][[:alpha:][:digit:]_]*
%%

{BLOCKCOMMENT}  /* do nothing */
{LINECOMMENT}  /* do nothing */

"int" return T_INT;
"bool" return T_BOOL;
"char" return T_CHAR;

"*" return CONT;
"&" return ADDR;

"(" return LPAREN;
")" return RPAREN;
"{" return LBRACE;
"}" return RBRACE;
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
"void" return VOID;
"if" return IF;
"else" return ELSE;
"while" return WHILE;
"for" return FOR;
"break" return BREAK;
"continue" return CONTINUE;
"return" return RETURN;

"printf" return PRINT;
"scanf" return SCAN;

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
    return IDENTIFIER;
}

{WHILTESPACE} /* do nothing */

{EOL} lineno++;

. {
    cerr << "[line "<< lineno <<" ] unknown character:" << yytext << endl;
}
%%