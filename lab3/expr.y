%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef YYSTYPE
#define YYSTYPE	char*
#endif
char idStr [50];
char numStr[50];
int yylex ();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s );
%}

%token NUMBER
%token ID
%token ADD
%token MINUS
%token MUL
%token DIV
%left ADD MINUS
%left MUL DIV
%right UMINUS


%%


lines	:	lines expr '\n' { printf("%s\n", $2); }
		|	lines '\n'
		|
		;

expr	:	expr ADD expr { $$ = (char*)malloc(strlen($1) + strlen($3) + 1); strcpy($$,$1); strcat($$,$3); strcat($$,"+"); }
		|	expr MINUS expr { $$ = (char*)malloc(strlen($1) + strlen($3) + 1); strcpy($$,$1); strcat($$,$3); strcat($$,"-"); }
		|	expr MUL expr { $$ = (char*)malloc(strlen($1) + strlen($3) + 1); strcpy($$,$1); strcat($$,$3); strcat($$,"*"); }
		|	expr DIV expr { $$ = (char*)malloc(strlen($1) + strlen($3) + 1); strcpy($$,$1); strcat($$,$3); strcat($$,"/"); }
		|	'(' expr')' { (char*)malloc(strlen($2) + 1); strcpy($$, $2); strcat($$," ");}
		|	NUMBER { $$ = (char*)malloc(strlen($1) + 1); strcpy($$, $1); strcat($$," ");}
		|	ID { $$ = (char*)malloc(strlen($1) + 1); strcpy($$, $1); strcat($$," ");}
		;


%%


// programs section
int yylex()
{
	// place your token retrieving code here
	char t;
	while (1) {
		t = getchar ();
		if (t == ' ' ||	t== '\t')
			;
		else if (( t >= '0' && t <= '9' )) {
			int ti = 0;
			while (( t >= '0' && t <= '9' )) {
				numStr[ti] = t;
				t = getchar();
				ti++;
			}
			numStr[ti] = '\0';
			yylval = numStr;
			ungetc(t , stdin);
			return NUMBER;
		}
		else if ((t>='a' && t<='z') || (t>='A' && t<='Z') || (t=='_')) {
			int ti=0;
			while ((t>='a' && t<='z') ||(t>='A' && t<='Z') || (t=='_') || (t>='0' && t<='9')) {
				idStr[ti]=t;
				ti++;
				t = getchar();
			}
			idStr[ti]='\0';
			yylval = idStr;
			ungetc(t, stdin);
			return ID;
		}
		else if (t=='+'){
			return ADD;
		}
		else if (t=='-'){
			return MINUS;
		}
		else if (t=='*'){
			return MUL;
		}
		else if (t=='/'){
			return DIV;
		}
		else { 
			return t; 
		}
	}
}

int main(void)
{
	yyin = stdin;
	do {
		yyparse();
	} while (!feof(yyin));
	return 0;
}

void yyerror(const char* s) {
	fprintf (stderr , "Parse error	:	%s\n", s );
	exit (1);
}
