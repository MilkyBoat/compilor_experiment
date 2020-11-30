%{
    #include "common.h"
    #define YYSTYPE TreeNode *  
    TreeNode* root;
    extern int lineno;
    int max_scope_id=1;
    stack<int> scope;
    int yylex();
    int yyerror( char const * );
%}

%token T_CHAR T_INT T_STRING T_BOOL 

%token CONT ADDR;

%token ASSIGN PLUSASSIGN MINUSASSIGN MULASSIGN DIVASSIGN

%token SEMICOLON LPAREN RPAREN LBRACE RBRACE

%token CONST VOID IF ELSE WHILE FOR BREAK CONTINUE RETURN

%token EQ GRAEQ LESEQ NEQ 

%token GRA LES PLUS MINUS MUL DIV MOD AND OR NOT

%token IDENTIFIER INTEGER CHAR BOOL STRING

%token PRINT SCAN

%left EQ

%%

program
: declaration {}
| funcdef {}
| program declaration {}
| program funcdef {}
| statements {root = new TreeNode(0, NODE_PROG); root->addChild($1);}
;

statements
:  statement {$$=$1;}
|  LBRACE statements RBRACE {$$=$2;}
|  statements statement {$$=$1; $$->addSibling($2);}
;

statement
: SEMICOLON  {$$ = new TreeNode(lineno, NODE_STMT); $$->stype = STMT_SKIP;}
| declaration SEMICOLON {$$ = $1;}
| IF LPAREN expr RPAREN statements {$$ = new TreeNode(lineno, NODE_STMT); $$->stype = STMT_IF;}
| WHILE LPAREN expr RPAREN statements {$$ = new TreeNode(lineno, NODE_STMT); $$->stype = STMT_WHILE;}
| FOR // TODO
;

declaration
: T IDENTIFIER ASSIGN expr{  // declare and init
    TreeNode* node = new TreeNode($1->lineno, NODE_STMT);
    node->stype = STMT_DECL;
    node->addChild($1);
    node->addChild($2);
    node->addChild($4);
    $$ = node;   
} 
| T IDENTIFIER {
    TreeNode* node = new TreeNode($1->lineno, NODE_STMT);
    node->stype = STMT_DECL;
    node->addChild($1);
    node->addChild($2);
    $$ = node;   
}
;

expr
: IDENTIFIER {
    $$ = $1;
}
| INTEGER {
    $$ = $1;
}
| CHAR {
    $$ = $1;
}
| STRING {
    $$ = $1;
}
;

T
: T_INT {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_INT;} 
| T_CHAR {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_CHAR;}
| T_BOOL {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_BOOL;}
;

%%

int yyerror(char const* message)
{
  cout << "error: " << message << ". at line " << lineno << endl;
  return -1;
}