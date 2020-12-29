%option nounput
%{
#include "common.h"

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
DECINT [0-9]+
HEXINT 0[Xx][0-9a-fA-F]+

BOOL (true)|(false)
STRING \"[^(\")]*\"
CHAR \'\\?.\'

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
    // 支持转义字符
    if (yytext[1] == '\\') {
        switch (yytext[2]) {
        case 'a':
            node->ch_val = 7;
            break;
        case 'b':
            node->ch_val = 8;
            break;
        case 'f':
            node->ch_val = 12;
            break;
        case 'n':
            node->ch_val = 10;
            break;
        case 'r':
            node->ch_val = 13;
            break;
        case 't':
            node->ch_val = 9;
            break;
        case 'v':
            node->ch_val = 11;
            break;
        case '\\':
            node->ch_val = 92;
            break;
        case '\'':
            node->ch_val = 39;
            break;
        case '"':
            node->ch_val = 34;
            break;
        case '?':
            node->ch_val = 63;
            break;
        default:
            node->ch_val = 0;
            break;
        }
    }
    else {
        node->ch_val = yytext[1];
    }
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
