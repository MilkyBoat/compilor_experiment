%option noyywrap
%top{
#include <math.h>
#include <iomanip>

}
%{
	int chars=0,words=0,lines=0;
%}

word [a-zA-Z]+
line \n
char .

%%

{word}	{words++;chars+=strlen(yytext);}
{line}	{lines++;}
{char}	{chars++;}

%%

int main() {

    yyFlexLexer lexer;
    lexer.yylex();
    std::cout<<std::setw(8)<<lines<<std::setw(8)<<words<<std::setw(8)<<chars<<std::endl;

    return 0;
}

