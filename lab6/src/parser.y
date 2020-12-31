%{
	#include "common.h"
	#define YYSTYPE TreeNode *

	TreeNode* root = new TreeNode(0, NODE_PROG);
	extern int lineno;

	extern bool parserError;

	// max_scope_id 是堆栈下一层结点的最大编号
	unsigned char max_scope_id = SCOPT_ID_BASE;
	string presentScope = "1";
	unsigned int top = 0;

	// multimap <标识符名称， 作用域> 变量名列表
	extern multimap<string, string> idNameList;
	// map <<标识符名称， 作用域>, 结点指针> 变量列表
	extern map<pair<string, string>, TreeNode*> idList;

	// 用于检查continue和break是否在循环内部
	bool inCycle = false;

	int yylex();
	int yyerror( char const * );
	int scopeCmp(string preScope, string varScope);
	void scopePush();
	void scopePop();
%}

// 类型
%token T_CHAR T_INT T_STRING T_BOOL T_VOID

// 取地址运算符
%token ADDR;

// 赋值运算符
%token ASSIGN PLUSASSIGN MINUSASSIGN MULASSIGN DIVASSIGN

// 括号分号逗号中括号
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

// 关键字
%token CONST IF_ ELSE WHILE_ FOR_ BREAK CONTINUE RETURN

// 比较运算符
%token EQ GRAEQ LESEQ NEQ  GRA LES

// 普通计算
%token PLUS MINUS MUL DIV MOD AND OR NOT INC DEC

// 特殊单词
%token IDENTIFIER INTEGER CHAR BOOL STRING

%left EQ

%%

program
: decl {root->addChild($1);}
| funcDef {root->addChild($1);}
| program decl {root->addChild($2);}
| program funcDef {root->addChild($2);}
;

// ---------------- 类型与复合标识符 -------------------

basicType
: T_INT {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_INT;}
| T_CHAR {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_CHAR;}
| T_BOOL {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_BOOL;}
| T_VOID {$$ = new TreeNode(lineno, NODE_TYPE); $$->type = TYPE_VOID;}
;

literalConst
: INTEGER {$$ = new TreeNode(lineno, NODE_EXPR); $$->addChild($1);}
| BOOL {$$ = new TreeNode(lineno, NODE_EXPR); $$->addChild($1);}
| CHAR {$$ = new TreeNode(lineno, NODE_EXPR); $$->addChild($1);}
| STRING {$$ = new TreeNode(lineno, NODE_EXPR); $$->addChild($1);}
;

// ------ 复合标识符，包含指针与数组，在变量声明外使用 -----
compIdentifier
: pIdentifier {$$ = $1;}
| arrayIdentifier {
	$$ = $1;
	// 归约完成，清除下标计数器，为下一次做准备
	$$->child->type->visitDim = 0;
  }
;

// 指针标识符
pIdentifier
: identifier {$$ = new TreeNode($1);}
| MUL pIdentifier {$$ = $2; $$->pointLevel++;}
| ADDR pIdentifier {
	$$ = $2; 
	$$->pointLevel--;
	if ($$->pointLevel < -2) {
		yyerror("Continuous addr operator");
	}
  }
;

// 数组标识符
arrayIdentifier
: pIdentifier LBRACKET expr RBRACKET {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_INDEX;
	$$->addChild($1);

	// 计算数组偏移量倍数
	int biasRate = 1;
	for (unsigned int i = $1->type->visitDim + 1; i < $1->type->dim; i++) {
		biasRate *= $1->type->dimSize[i];
	}
	TreeNode* biasNode;
	if (biasRate == 1) {
		// 偏移倍数为1时省略乘法结点
		biasNode = $3;
	}
	else {
		biasNode = new TreeNode(lineno, NODE_OP);
		biasNode->optype = OP_MUL;
		biasNode->addChild($3);
		TreeNode* biasRateExpr = new TreeNode(lineno, NODE_EXPR);
		TreeNode* biasRateConst = new TreeNode(lineno, NODE_CONST);
		biasRateConst->type = TYPE_INT;
		biasRateConst->int_val = biasRate;
		biasRateExpr->addChild(biasRateConst);
		biasNode->addChild(biasRateExpr);
	}
	$1->type->visitDim++;

	$$->addChild(biasNode);
  }
| arrayIdentifier LBRACKET expr RBRACKET {
	$$ = $1;
	TreeNode* newBiasNode = new TreeNode(lineno, NODE_OP);
	newBiasNode->optype = OP_ADD;
	newBiasNode->addChild($$->child->sibling);
	$$->child->sibling = newBiasNode;

	// 计算数组偏移量倍数
	int biasRate = 1;
	for (unsigned int i = $$->child->type->visitDim + 1; i < $$->child->type->dim; i++) {
		biasRate *= $$->child->type->dimSize[i];
	}

	TreeNode* biasNode;
	if (biasRate == 1) {
		// 偏移倍数为1时省略乘法结点
		biasNode = $3;
	}
	else {
		biasNode->optype = OP_MUL;
		biasNode->addChild($3);
		TreeNode* biasRateExpr = new TreeNode(lineno, NODE_EXPR);
		TreeNode* biasRateConst = new TreeNode(lineno, NODE_CONST);
		biasRateConst->type = TYPE_INT;
		biasRateConst->int_val = biasRate;
		biasRateExpr->addChild(biasRateConst);
		biasNode->addChild(biasRateExpr);
	}
	$$->child->type->visitDim++;
	newBiasNode->addChild(biasNode);
  }
;

identifier
: IDENTIFIER {
	$$ = $1;
	int idNameCount = idNameList.count($$->var_name);
	int declCnt = 0;
	int minDefDis = MAX_SCOPE_STACK;

	// 搜索变量是否已经声明
	auto it = idNameList.find($$->var_name);
	int resScoptCmp;
	while (idNameCount--) {
		resScoptCmp = scopeCmp(presentScope, it->second);
		if (resScoptCmp >= 0){
			// 寻找最近的定义
			if (resScoptCmp < minDefDis) {
				minDefDis = resScoptCmp;
				$$ = idList[make_pair(it->first, it->second)];
			}
			declCnt++;
		}
		it++;
	}
	if (declCnt == 0) {
		string t = "Undeclared identifier :'" + $1->var_name + "', scope : " + to_string(resScoptCmp);
		yyerror(t.c_str());
	}
};

// --------- 声明用标识符 ----------
declCompIdentifier
: pDeclIdentifier {$$ = $1;}
| arrayDeclIdentifier {$$ = $1;}
;

pDeclIdentifier
: declIdentifier {$$ = $1;}
| MUL pDeclIdentifier {$$ = $2; $$->type->pointLevel++;}
| ADDR pDeclIdentifier {$$ = $2; $$->type->pointLevel--;}
;

// 常量数组标识符（仅供声明使用）
arrayDeclIdentifier
: pDeclIdentifier LBRACKET INTEGER RBRACKET {
  $$ = $1;
  $$->type->type = VALUE_ARRAY;
  $$->type->elementType = $1->type->type;
  $$->type->dimSize[$$->type->dim] = $3->int_val;
  $$->type->dim++;
}
| arrayDeclIdentifier LBRACKET INTEGER RBRACKET {
  $$ = $1;
  $$->type->dimSize[$$->type->dim] = $3->int_val;
  $$->type->dim++;
}
;

declIdentifier
: IDENTIFIER {
	$$ = $1;
	$$->var_scope = presentScope;
	$$->type = new Type(NOTYPE);
	#ifdef ID_REDUCE_DEBUG
		cout<<"# $ reduce declIdentifier : "<<$$->var_name<<", at scope :"<<presentScope<<endl;
	#endif
	if (idList.count(make_pair($$->var_name, $$->var_scope)) != 0) {
		string t = "Redeclared identifier : " + $$->var_name;
		yyerror(t.c_str());
	}
	idNameList.insert(make_pair($$->var_name, $$->var_scope));
	idList[make_pair($$->var_name, $$->var_scope)] = $$;
}
;

// ---------------- 常变量声明 -------------------

decl
: constDecl {$$ = $1;}
| varDecl {$$ = $1;}
;

constDecl
: CONST basicType constDefs SEMICOLON {
  $$ = new TreeNode(lineno, NODE_STMT);
  $$->stype = STMT_CONSTDECL;
  $$->type = TYPE_NONE;
  $$->addChild($2);
  $$->addChild($3);  
  TreeNode* p = $3->child;
  while(p != nullptr) {
	  p->child->type->copy($2->type);
	  p->child->type->constvar = true;
	  p = p->sibling;
  }
};

// 连续常量定义
constDefs
: constDef {$$ = new TreeNode(lineno, NODE_VARLIST); $$->addChild($1);}
| constDefs COMMA constDef {$$ = $1; $$->addChild($3);}
;

constDef
: pDeclIdentifier ASSIGN literalConst {
	$$ = new TreeNode(lineno, NODE_OP); 
	$$->optype = OP_DECLASSIGN;
	$$->addChild($1); 
	$$->addChild($3);
  }
| arrayDeclIdentifier ASSIGN LBRACE ArrayInitVal RBRACE {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_DECLASSIGN;
	$$->addChild($1); 
	$$->addChild($4);
  }
;

// 数组初始化值
ArrayInitVal
: literalConst {$$ = new TreeNode(lineno, NODE_VARLIST); $$->addChild($1);}
| ArrayInitVal COMMA literalConst {$$ = $1; $$->addChild($3);}
;

varDecl
: basicType varDefs SEMICOLON {
  $$ = new TreeNode(lineno, NODE_STMT);
  $$->stype = STMT_DECL;
  $$->type = TYPE_NONE;
  $$->addChild($1);
  $$->addChild($2);
  TreeNode* p = $2->child;
  while(p != nullptr) {
	  if (p->nodeType == NODE_OP) {
		  p->child->type->copy($1->type);
	  }
	  else {
	  	p->type->copy($1->type);
	  }
	  p = p->sibling;
  }
  #ifdef DECL_DEBUG
	cout << "# $ reduce varDecl type = " << $1->type->getTypeInfo() << endl;
	// $$->printAST();
  #endif
}
;

// 连续变量定义
varDefs
: varDef {$$ = new TreeNode(lineno, NODE_VARLIST); $$->addChild($1);}
| varDefs COMMA varDef {$$ = $1; $$->addChild($3);}
;

varDef
: declCompIdentifier {$$ = $1;}
| declCompIdentifier ASSIGN expr {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_DECLASSIGN;
	$$->addChild($1);
	$$->addChild($3);
  }
| arrayDeclIdentifier ASSIGN LBRACE ArrayInitVal RBRACE {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_DECLASSIGN;
	$$->addChild($1);
	$$->addChild($4);
  }
;

// ---------------- 函数声明 -------------------

funcDef
: basicType pDeclIdentifier funcLPAREN funcFParams RPAREN LBRACE blockItems RBRACE {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_FUNCDECL;
	$2->type->type = COMPOSE_FUNCTION;
	TreeNode* param = $4;
	while (param != nullptr) {
		$2->type->paramType[$2->type->paramNum] = param->child->type;
		$2->type->paramNum++;
		param = param->sibling;
	}
	$2->type->retType = $1->type;
	$$->addChild($1);
	$$->addChild($2);
	TreeNode* params = new TreeNode(lineno, NODE_VARLIST);
	params->addChild($4);
	$$->addChild(params);
	TreeNode* funcBlock = new TreeNode(lineno, NODE_STMT);
	funcBlock->stype = STMT_BLOCK;
	funcBlock->addChild($7);
	$$->addChild(funcBlock);
	scopePop();
  }
| basicType pDeclIdentifier funcLPAREN RPAREN LBRACE blockItems RBRACE {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_FUNCDECL;
	$2->type->type = COMPOSE_FUNCTION;
	$2->type->retType = $1->type;
	$$->addChild($1);
	$$->addChild($2);
	$$->addChild(new TreeNode(lineno, NODE_VARLIST));
	TreeNode* funcBlock = new TreeNode(lineno, NODE_STMT);
	funcBlock->stype = STMT_BLOCK;
	funcBlock->addChild($6);
	$$->addChild(funcBlock);
	scopePop();
  }
;

funcLPAREN : LPAREN {scopePush();};

funcFParams
: funcFParam {$$ = $1;}
| funcFParams COMMA funcFParam {$$ = $1; $$->addSibling($3);}
;

funcFParam
: basicType pDeclIdentifier {
	$$ = new TreeNode(lineno, NODE_PARAM); 
	$$->addChild($1); 
	$$->addChild($2);
	$2->type->copy($1->type);
  }
;

// ---------------- 语句块 -------------------

block
: blockLBRACE blockItems blockRBRACE {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_BLOCK;
	$$->addChild($2);
};

blockLBRACE : LBRACE {scopePush();}
blockRBRACE : RBRACE {scopePop();}

blockItems
: blockItem {$$ = $1;}
| blockItems blockItem {$$ = $1; $$->addSibling($2);}
;

blockItem
: decl {$$ = $1;}
| stmt {$$ = $1;}
;

stmt_
: LBRACE blockItems RBRACE {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_BLOCK;
	$$->addChild($2);
  }
| stmt {$$ = $1;}
;

stmt
: SEMICOLON {$$ = new TreeNode(lineno, NODE_STMT); $$->stype = STMT_SKIP;}
| expr SEMICOLON {$$ = $1;}
| block {$$ = $1;}
| IF LPAREN cond RPAREN stmt_ ELSE stmt_ {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_IFELSE;
	$$->addChild($3);
	$$->addChild($5);
	$$->addChild($7);
	scopePop();
	#ifdef IFELSE_DEBUG
		cout << "# $ reduce IF-ELSE at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
| IF LPAREN cond RPAREN stmt_ {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_IF;
	$$->addChild($3);
	$$->addChild($5);
	scopePop();
	#ifdef IF_DEBUG
		cout << "% # $ reduce IF at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
| WHILE LPAREN cond RPAREN stmt_ {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_WHILE;
	$$->addChild($3);
	$$->addChild($5);
	inCycle = false;
	scopePop();
	#ifdef WHILE
		cout << "# $ reduce WHILE at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
| FOR LPAREN basicType varDefs SEMICOLON cond SEMICOLON expr RPAREN stmt_ {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_FOR;
	TreeNode* forDecl = new TreeNode(lineno, NODE_STMT);
	forDecl->stype = STMT_DECL;
	forDecl->addChild($3);
	TreeNode* p = $4->child;
	while (p) {
		if (p->nodeType == NODE_OP) {
			p->child->type->copy($3->type);
		}
		else {
			p->type->copy($3->type);
		}
		p = p->sibling;
	}
	forDecl->addChild($4);
	$$->addChild(forDecl);
	$$->addChild($6);
	$$->addChild($8);
	$$->addChild($10);
	inCycle = false;
	scopePop();
  }
| FOR LPAREN expr SEMICOLON cond SEMICOLON expr RPAREN stmt_ {
	$$ = new TreeNode(lineno, NODE_STMT);
	$$->stype = STMT_FOR;
	$$->addChild($3);
	$$->addChild($5);
	$$->addChild($7);
	$$->addChild($9);
	inCycle = false;
	scopePop();
  }

| BREAK SEMICOLON {
	if (!inCycle) {
		yyerror("break statement outside loop");
	}
	$$ = new TreeNode(lineno, NODE_STMT); 
	$$->stype = STMT_BREAK; 
	$$->type = TYPE_NONE;
  }
| CONTINUE SEMICOLON{
	if (!inCycle) {
		yyerror("continue statement outside loop");
	}
	$$ = new TreeNode(lineno, NODE_STMT); 
	$$->stype = STMT_CONTINUE; 
	$$->type = TYPE_NONE;
  }
| RETURN SEMICOLON {$$ = new TreeNode(lineno, NODE_STMT); $$->stype = STMT_RETURN; $$->type = TYPE_NONE;}
| RETURN expr SEMICOLON {$$ = new TreeNode(lineno, NODE_STMT); $$->stype = STMT_RETURN; $$->addChild($2); $$->type = TYPE_NONE;}
;

IF : IF_ {scopePush();};
WHILE : WHILE_ {inCycle = true; scopePush();};
FOR : FOR_ {inCycle = true; scopePush();};

// ---------------- 表达式 -------------------

expr
: addExpr {$$ = $1;}
| compIdentifier ASSIGN expr {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_ASSIGN;
	$$->addChild($1);
	$$->addChild($3);
	#ifdef ASSIGN_DEBUG
		cout << "# $ reduce ASSIGN at scope : " << presentScope << ", at line " << lineno << endl;
		// $$->printAST();
	#endif
  }
| compIdentifier PLUSASSIGN expr {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_ADDASSIGN;
	$$->addChild($1);
	$$->addChild($3);
  }
| compIdentifier MINUSASSIGN expr {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_SUBASSIGN;
	$$->addChild($1);
	$$->addChild($3);
  }
| compIdentifier MULASSIGN expr {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_MULASSIGN;
	$$->addChild($1);
	$$->addChild($3);
  }
| compIdentifier DIVASSIGN expr {
	$$ = new TreeNode(lineno, NODE_OP);
	$$->optype = OP_DIVASSIGN;
	$$->addChild($1);
	$$->addChild($3);
  }
;

cond
: LOrExpr {$$ = $1;}
;

addExpr
: mulExpr {$$ = $1;}
| addExpr PLUS mulExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_ADD; $$->addChild($1); $$->addChild($3);}
| addExpr MINUS mulExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_SUB; $$->addChild($1); $$->addChild($3);}
;

// factor
mulExpr
: unaryExpr {$$ = $1;}
| mulExpr MUL unaryExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_MUL; $$->addChild($1); $$->addChild($3);}
| mulExpr DIV unaryExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_DIV; $$->addChild($1); $$->addChild($3);}
| mulExpr MOD unaryExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_MOD; $$->addChild($1); $$->addChild($3);}
;

// 一元表达式
unaryExpr
: primaryExpr {$$ = $1;}
| NOT cond {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_NOT; $$->addChild($2);}
| PLUS primaryExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_POS; $$->addChild($2);}
| MINUS primaryExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_NAG; $$->addChild($2);}
| pIdentifier INC {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_INC; $$->addChild($1);}
| pIdentifier DEC {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_DEC; $$->addChild($1);}
;

// 基本表达式
primaryExpr
: literalConst {$$ = $1;}
| LPAREN expr RPAREN {$$ = $2;}
| LPAREN cond RPAREN {$$ = $2;}
| pIdentifier LPAREN funcRParams RPAREN {
	$$ = new TreeNode(lineno, NODE_FUNCALL);
	$$->addChild($1);
	$$->addChild($3);
	#ifdef FUNCALL_DEBUG
		cout << "# $ reduce function call at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
| pIdentifier LPAREN RPAREN {
	$$ = new TreeNode(lineno, NODE_FUNCALL);
	$$->addChild($1);
	$$->addChild(new TreeNode(lineno, NODE_VARLIST));
	#ifdef FUNCALL_DEBUG
		cout << "# $ reduce function call at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
| compIdentifier {$$ = new TreeNode(lineno, NODE_EXPR); $$->addChild($1);}
;

// 函数实参列表
funcRParams
: expr {$$ = new TreeNode(lineno, NODE_VARLIST); $$->addChild($1);}
| funcRParams COMMA expr {$$ = $1; $$->addChild($3);}
;

// 或表达式
LOrExpr
: LAndExpr {$$ = $1;}
| LAndExpr OR LOrExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_OR; $$->addChild($1); $$->addChild($3);}
;

// 与
LAndExpr
: eqExpr {$$ = $1;}
| eqExpr AND LAndExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_AND; $$->addChild($1); $$->addChild($3);}
;

// 相等关系
eqExpr
: relExpr {$$ = $1;}
| relExpr EQ eqExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_EQ; $$->addChild($1); $$->addChild($3);}
| relExpr NEQ eqExpr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_NEQ; $$->addChild($1); $$->addChild($3);}
;

// 相对关系
relExpr
: expr {$$ = $1;}
| relExpr GRA expr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_GRA; $$->addChild($1); $$->addChild($3);}
| relExpr LES expr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_LES; $$->addChild($1); $$->addChild($3);}
| relExpr GRAEQ expr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_GRAEQ; $$->addChild($1); $$->addChild($3);}
| relExpr LESEQ expr {$$ = new TreeNode(lineno, NODE_OP); $$->optype = OP_LESEQ; $$->addChild($1); $$->addChild($3);}
;

%%

int yyerror(char const * message)
{
	cout << "error: " << message << ", at line " << lineno << endl;
	parserError = true;
#ifdef EXIT_AT_GRAMMA_ERROR
	exit(0);
#else
	return 0;
#endif
}

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
