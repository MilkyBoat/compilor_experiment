%option noyywrap
%top{
#include <math.h>
}
%{
	int id_num = 0;
	char id_list[100][20];
%}

commentbegin "/*"
commentelement .|\n
commentend "*/"
%x COMMENT
commentlinebegin "//"
commentlineelement .
commentlineend \n
%x COMMENTLINE

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
BREAK "break"
CONTINUE "continue"
RETURN "return"
INT "int"

OCTNUMBER 0[0-7]+
DECNUMBER -?[0-9]+
HEXNUMBER 0[Xx][0-9a-fA-F]+
ID [a-zA-Z_][a-zA-Z0-9_]*

FORMATCHAR [\r\n\t ]+

%%

{FORMATCHAR} {;}
{LPAREN} {fprintf(yyout, "%12s%8s\n", "LPAREN", yytext);}
{RPAREN} {fprintf(yyout, "%12s%8s\n", "RPAREN", yytext);}
{LBRACE} {fprintf(yyout, "%12s%8s\n", "LBRACE", yytext);}
{RBRACE} {fprintf(yyout, "%12s%8s\n", "RBRACE", yytext);}
{SEMICOLON} {fprintf(yyout, "%12s%8s\n", "SEMICOLON", yytext);}

{ASSIGN} {fprintf(yyout, "%12s%8s\n", "ASSIGN", yytext);}
{PLUSASSIGN} {fprintf(yyout, "%12s%8s\n", "PLUSASSIGN", yytext);}
{MINUSASSIGN} {fprintf(yyout, "%12s%8s\n", "MINUSASSIGN", yytext);}
{MULASSIGN} {fprintf(yyout, "%12s%8s\n", "MULASSIGN", yytext);}
{DIVASSIGN} {fprintf(yyout, "%12s%8s\n", "DIVASSIGN", yytext);}
{EQ} {fprintf(yyout, "%12s%8s\n", "EQ", yytext);}
{NEQ} {fprintf(yyout, "%12s%8s\n", "NEQ", yytext);}
{GRA} {fprintf(yyout, "%12s%8s\n", "GRA", yytext);}
{LES} {fprintf(yyout, "%12s%8s\n", "LES", yytext);}
{GRAEQ} {fprintf(yyout, "%12s%8s\n", "GRAEQ", yytext);}
{LESEQ} {fprintf(yyout, "%12s%8s\n", "LESEQ", yytext);}
{PLUS} {fprintf(yyout, "%12s%8s\n", "PLUS", yytext);}
{MINUS} {fprintf(yyout, "%12s%8s\n", "MINUS", yytext);}
{MUL} {fprintf(yyout, "%12s%8s\n", "MUL", yytext);}
{DIV} {fprintf(yyout, "%12s%8s\n", "DIV", yytext);}
{MOD} {fprintf(yyout, "%12s%8s\n", "MOD", yytext);}
{AND} {fprintf(yyout, "%12s%8s\n", "AND", yytext);}
{OR} {fprintf(yyout, "%12s%8s\n", "OR", yytext);}
{NOT} {fprintf(yyout, "%12s%8s\n", "NOT", yytext);}

{CONST} {fprintf(yyout, "%12s%8s\n", "CONST", yytext);}
{VOID} {fprintf(yyout, "%12s%8s\n", "VOID", yytext);}
{IF} {fprintf(yyout, "%12s%8s\n", "IF", yytext);}
{ELSE} {fprintf(yyout, "%12s%8s\n", "ELSE", yytext);}
{WHILE} {fprintf(yyout, "%12s%8s\n", "WHILE", yytext);}
{BREAK} {fprintf(yyout, "%12s%8s\n", "BREAK", yytext);}
{CONTINUE} {fprintf(yyout, "%12s%8s\n", "CONTINUE", yytext);}
{RETURN} {fprintf(yyout, "%12s%8s\n", "RETURN", yytext);}

{INT} {fprintf(yyout, "%12s%8s\n", "INT", yytext);}

{OCTNUMBER} {fprintf(yyout, "%12s%8s%8s\n", "OCTNUMBER", yytext, yytext);}
{DECNUMBER} {fprintf(yyout, "%12s%8s%8s\n", "DECNUMBER", yytext, yytext);}
{HEXNUMBER} {fprintf(yyout, "%12s%8s%8s\n", "HEXNUMBER", yytext, yytext);}
{ID} {
	_Bool id_match = 0;
	int id = 0;
	for (int i = 0; i < id_num; i++) {
		if (strcmp(yytext, id_list[i])==0) {
			id_match = 1;
			id = i;
			break;
		}
	}
	if (!id_match) {
		id = id_num;
		strcpy(id_list[id], yytext);
		id_num++;
	}
	fprintf(yyout, "%12s%8s%8d\n", "ID", yytext, id);
}

{commentbegin} {BEGIN COMMENT;}
<COMMENT>{commentelement} {}
<COMMENT>{commentend} {BEGIN INITIAL;}
{commentlinebegin} {BEGIN COMMENTLINE;}
<COMMENTLINE>{commentlineelement} {}
<COMMENTLINE>{commentlineend} {BEGIN INITIAL;}

%%

int main() {
	yylex();
	return 0;
}
