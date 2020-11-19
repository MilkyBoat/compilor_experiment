%{
    #include"common.h"
    extern TreeNode * root;
    int yylex();
    int yyerror( char const * );
%}
%defines

%start program

%token ID INTEGER
%token IF ELSE WHILE
%token INT VOID
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token TRUE FALSE
%token ADD ASSIGN EQUAL NOT
%token PRINTF SCANF

%right NOT
%left ADD
%left EQUAL
%right ASSIGN
%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE 
%%
program
    : statements {root=new TreeNode(NODE_PROG);root->addChild($1);}
    ;
statements
    : statement {$$=$1;}
    | statements statement{$$=$1;$$->addSibling($2);}
    ;
statement
    : instruction {$$=$1;}
    | if_else {$$=$1;}
    | while {$$=$1;}
    | LBRACE statements RBRACE {$$=$2;}
    ;
if_else
    : IF bool_statment statement %prec LOWER_THEN_ELSE {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_IF;
        node->addChild($2);
        node->addChild($3);
        $$=node;
    }
    | IF bool_statment statement ELSE statement {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_IF;
        node->addChild($2);
        node->addChild($3);
        node->addChild($5);
        $$=node;
    }
    ;
while
    : WHILE bool_statment statement {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_WHILE;
        node->addChild($2);
        node->addChild($3);
        $$=node;
    }
    ;
bool_statment
    : LPAREN bool_expr RPAREN {$$=$2;}
    ;
instruction
    : type ID ASSIGN expr SEMICOLON {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_DECL;
        node->addChild($1);
        node->addChild($2);
        node->addChild($4);
        $$=node;
    }
    | ID ASSIGN expr SEMICOLON {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_ASSIGN;
        node->addChild($1);
        node->addChild($3);
        $$=node;  
    }
    | printf SEMICOLON {$$=$1;}
    | scanf SEMICOLON {$$=$1;}
    ;
printf
    : PRINTF LPAREN expr RPAREN {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_PRINTF;
        node->addChild($3);
        $$=node;
    }
    ;
scanf
    : SCANF LPAREN expr RPAREN {
        TreeNode *node=new TreeNode(NODE_STMT);
        node->stmtType=STMT_SCANF;
        node->addChild($3);
        $$=node;
    }
    ;
bool_expr
    : TRUE {$$=$1;}
    | FALSE {$$=$1;}
    | expr EQUAL expr {
        TreeNode *node=new TreeNode(NODE_OP);
        node->opType=OP_EQUAL;
        node->addChild($1);
        node->addChild($3);
        $$=node;
    }
    | NOT bool_expr {
        TreeNode *node=new TreeNode(NODE_OP);
        node->opType=OP_NOT;
        node->addChild($2);
        $$=node;        
    }
    ;
expr
    : ID {$$=$1;}
    | INTEGER {$$=$1;}
    | expr ADD expr {
        TreeNode *node=new TreeNode(NODE_OP);
        node->opType=OP_ADD;
        node->addChild($1);
        node->addChild($3);
        $$=node;   
    }
    ;
type
    : INT {
        TreeNode *node=new TreeNode(NODE_TYPE);
        node->varType=VAR_INTEGER;
        $$=node; 
    }
    | VOID {
        TreeNode *node=new TreeNode(NODE_TYPE);
        node->varType=VAR_VOID;
        $$=node;         
    }
    ;

%%