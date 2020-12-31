/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/parser.y" /* yacc.c:339  */

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

#line 95 "src/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_SRC_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_CHAR = 258,
    T_INT = 259,
    T_STRING = 260,
    T_BOOL = 261,
    T_VOID = 262,
    ADDR = 263,
    ASSIGN = 264,
    PLUSASSIGN = 265,
    MINUSASSIGN = 266,
    MULASSIGN = 267,
    DIVASSIGN = 268,
    SEMICOLON = 269,
    COMMA = 270,
    LPAREN = 271,
    RPAREN = 272,
    LBRACE = 273,
    RBRACE = 274,
    LBRACKET = 275,
    RBRACKET = 276,
    CONST = 277,
    IF_ = 278,
    ELSE = 279,
    WHILE_ = 280,
    FOR_ = 281,
    BREAK = 282,
    CONTINUE = 283,
    RETURN = 284,
    EQ = 285,
    GRAEQ = 286,
    LESEQ = 287,
    NEQ = 288,
    GRA = 289,
    LES = 290,
    PLUS = 291,
    MINUS = 292,
    MUL = 293,
    DIV = 294,
    MOD = 295,
    AND = 296,
    OR = 297,
    NOT = 298,
    INC = 299,
    DEC = 300,
    IDENTIFIER = 301,
    INTEGER = 302,
    CHAR = 303,
    BOOL = 304,
    STRING = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 197 "src/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   529

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  220

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    60,    61,    62,    68,    69,    70,    71,
      75,    76,    77,    78,    83,    84,    93,    94,    95,   106,
     136,   170,   199,   200,   204,   205,   206,   211,   218,   226,
     245,   246,   250,   266,   267,   271,   277,   287,   288,   292,
     317,   318,   322,   323,   329,   340,   362,   378,   381,   382,
     386,   397,   403,   404,   407,   408,   412,   413,   417,   422,
     426,   427,   428,   429,   440,   450,   461,   485,   496,   504,
     512,   513,   516,   517,   518,   523,   524,   534,   540,   546,
     552,   561,   565,   566,   567,   572,   573,   574,   575,   580,
     581,   582,   583,   584,   585,   590,   591,   592,   593,   601,
     609,   614,   615,   620,   621,   626,   627,   632,   633,   634,
     639,   640,   641,   642,   643
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_CHAR", "T_INT", "T_STRING", "T_BOOL",
  "T_VOID", "ADDR", "ASSIGN", "PLUSASSIGN", "MINUSASSIGN", "MULASSIGN",
  "DIVASSIGN", "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "CONST", "IF_", "ELSE", "WHILE_",
  "FOR_", "BREAK", "CONTINUE", "RETURN", "EQ", "GRAEQ", "LESEQ", "NEQ",
  "GRA", "LES", "PLUS", "MINUS", "MUL", "DIV", "MOD", "AND", "OR", "NOT",
  "INC", "DEC", "IDENTIFIER", "INTEGER", "CHAR", "BOOL", "STRING",
  "$accept", "program", "basicType", "literalConst", "compIdentifier",
  "pIdentifier", "arrayIdentifier", "identifier", "declCompIdentifier",
  "pDeclIdentifier", "arrayDeclIdentifier", "declIdentifier", "decl",
  "constDecl", "constDefs", "constDef", "ArrayInitVal", "varDecl",
  "varDefs", "varDef", "funcDef", "funcLPAREN", "funcFParams",
  "funcFParam", "block", "blockLBRACE", "blockRBRACE", "blockItems",
  "blockItem", "stmt_", "stmt", "IF", "WHILE", "FOR", "expr", "cond",
  "addExpr", "mulExpr", "unaryExpr", "primaryExpr", "funcRParams",
  "LOrExpr", "LAndExpr", "eqExpr", "relExpr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -173

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-173)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     103,  -173,  -173,  -173,  -173,   155,    76,     2,  -173,  -173,
    -173,  -173,     2,  -173,  -173,  -173,     2,     2,  -173,    -2,
      27,    11,  -173,    43,  -173,    13,    21,    70,  -173,  -173,
    -173,   479,  -173,   -26,   114,    17,    64,  -173,     2,   124,
      97,  -173,     2,     4,   479,   119,   119,     4,   479,  -173,
    -173,  -173,  -173,  -173,  -173,   138,     7,    99,  -173,  -173,
     127,   139,  -173,  -173,   101,   106,     2,    53,  -173,   124,
     115,   120,  -173,  -173,   124,  -173,  -173,   159,   170,  -173,
     164,   156,   451,  -173,    33,  -173,  -173,  -173,  -173,  -173,
     479,   479,   479,   479,   479,   427,   479,  -173,  -173,   479,
     479,   479,   479,   479,   479,  -173,   374,  -173,   155,   181,
    -173,    62,  -173,    82,  -173,  -173,   479,   479,   479,   479,
     479,   479,   479,   479,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,    79,   135,   191,   139,   139,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,   199,   200,   464,     2,  -173,  -173,
     374,   182,  -173,  -173,   201,   205,   206,   202,  -173,   374,
     124,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,   479,  -173,  -173,  -173,  -173,  -173,  -173,   209,   230,
    -173,  -173,   479,   479,    96,  -173,   278,  -173,  -173,  -173,
    -173,  -173,   198,   207,     2,   212,  -173,   411,   411,   167,
     479,   374,   203,  -173,  -173,   479,   221,   326,   411,   225,
     479,  -173,  -173,   479,   223,   224,   411,   411,  -173,  -173
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     6,     8,     9,     0,     0,     0,     2,    30,
      31,     3,     0,     1,     4,     5,     0,     0,    29,    42,
      22,    23,    24,     0,    40,     0,     0,     0,    33,    26,
      25,     0,    47,     0,     0,     0,     0,    39,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,    21,
      10,    12,    11,    13,    95,   100,    14,    15,    16,    43,
      75,    82,    85,    89,     0,     0,     0,     0,    48,     0,
       0,    22,    41,    35,     0,    34,    18,   110,     0,    81,
     103,   105,   107,   100,    14,    91,    92,    17,   110,    90,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,     0,     0,     0,     0,    27,     0,    50,     0,     0,
      37,     0,    28,     0,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    99,
     101,     0,     0,     0,    83,    84,    86,    87,    88,    60,
      52,    72,    73,    74,     0,     0,     0,     0,    56,    62,
       0,     0,    54,    57,     0,     0,     0,     0,    49,     0,
       0,    44,    36,   104,   106,   108,   113,   114,   109,   111,
     112,     0,    98,    19,    20,    68,    69,    70,     0,     0,
      46,    55,     0,     0,     0,    61,     0,    38,   102,    71,
      53,    51,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,    64,    59,    65,     0,     0,     0,     0,     0,
       0,    58,    63,     0,     0,     0,     0,     0,    67,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,     0,   -37,   -29,    83,  -173,  -173,  -173,    12,
      -4,  -173,     9,  -173,  -173,   208,   168,  -173,    49,   213,
     239,  -173,  -173,   146,  -173,  -173,  -173,  -146,  -140,  -103,
    -172,  -173,  -173,  -173,   -30,   -45,  -173,    94,    89,   157,
    -173,   131,   143,   -62,  -173
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,   147,    54,    55,    56,    57,    58,    19,    71,
      21,    22,   148,     9,    27,    28,   111,    10,    23,    24,
      11,    34,    67,    68,   149,   150,   191,   151,   152,   202,
     153,   154,   155,   156,   157,    78,    60,    61,    62,    63,
     131,    79,    80,    81,    82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       7,    59,    73,    89,   179,    12,     7,    31,    26,     8,
      16,   181,    43,   186,    77,    14,    83,    83,    88,    20,
      35,    64,    39,    95,    25,   203,   203,    96,    29,    30,
      40,    36,   110,    33,    66,    69,   203,   110,    26,   181,
      17,    36,    47,    32,   203,   203,   181,    33,    18,    95,
      49,    97,    98,    96,    25,   207,   165,    37,    38,   168,
     124,   125,   126,   127,   128,   130,   132,   181,   108,   133,
     109,    83,    83,    83,    83,    83,    13,   160,   107,     1,
       2,   161,     3,     4,    41,    42,    88,    88,    88,   166,
     167,    88,   169,   170,   171,   204,   172,   160,     5,     1,
       2,   162,     3,     4,    43,   212,     1,     2,    66,     3,
       4,    70,    44,   218,   219,    74,   178,     1,     2,    99,
       3,     4,   105,   187,   106,     5,    76,    43,    84,    84,
      87,    65,    45,    46,    47,    44,   112,   192,   193,    48,
      33,   188,    49,    50,    51,    52,    53,    90,    91,    92,
      93,    94,    88,    88,   195,   206,   173,    47,     1,     2,
     209,     3,     4,   100,   101,    49,    50,    51,    52,    53,
      88,    50,    51,    52,    53,    88,   114,   102,   103,   104,
     214,   205,    38,   215,   194,     1,     2,   115,     3,     4,
      43,   136,   137,   138,   134,   135,   139,   117,    44,   159,
     140,   180,    85,    86,     5,   141,   116,   142,   143,   144,
     145,   146,   174,   175,   176,   197,   185,   182,    45,    46,
      47,   183,   184,   189,   198,    48,   200,   208,    49,    50,
      51,    52,    53,     1,     2,   210,     3,     4,    43,   213,
     216,   217,   113,   199,   139,    15,    44,   163,   140,   190,
      75,    72,     5,   141,   158,   142,   143,   144,   145,   146,
     164,     0,     0,     0,     0,     0,    45,    46,    47,     0,
       0,     0,     0,    48,     0,     0,    49,    50,    51,    52,
      53,     1,     2,     0,     3,     4,    43,     0,     0,     0,
       0,     0,   139,     0,    44,     0,   140,   196,     0,     0,
       5,   141,     0,   142,   143,   144,   145,   146,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,     0,
       0,    48,     0,     0,    49,    50,    51,    52,    53,     1,
       2,     0,     3,     4,    43,     0,     0,     0,     0,     0,
     139,     0,    44,     0,   140,   211,     0,     0,     5,   141,
       0,   142,   143,   144,   145,   146,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,    48,
       0,     0,    49,    50,    51,    52,    53,     1,     2,     0,
       3,     4,    43,     0,     0,     0,     0,     0,   139,     0,
      44,     0,   140,     0,     0,     0,     5,   141,     0,   142,
     143,   144,   145,   146,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,    48,     0,    43,
      49,    50,    51,    52,    53,   139,     0,    44,     0,   201,
       0,     0,     0,     0,   141,    43,   142,   143,   144,   145,
     146,     0,     0,    44,   129,     0,     0,    45,    46,    47,
       0,     0,     0,     0,    48,     0,     0,    49,    50,    51,
      52,    53,     0,    45,    46,    47,     0,     0,     0,     0,
      48,     0,    43,    49,    50,    51,    52,    53,   177,     0,
      44,   118,   119,   120,   121,   122,   123,    43,     0,     0,
       0,     0,     0,     0,     0,    44,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,    48,     0,     0,
      49,    50,    51,    52,    53,    45,    46,    47,     0,     0,
       0,     0,    48,     0,     0,    49,    50,    51,    52,    53
};

static const yytype_int16 yycheck[] =
{
       0,    31,    39,    48,   150,     5,     6,     9,    12,     0,
       8,   151,     8,   159,    44,     6,    45,    46,    48,     7,
       9,    47,     9,    16,    12,   197,   198,    20,    16,    17,
       9,    20,    69,    20,    34,    18,   208,    74,    42,   179,
      38,    20,    38,    16,   216,   217,   186,    20,    46,    16,
      46,    44,    45,    20,    42,   201,   118,    14,    15,   121,
      90,    91,    92,    93,    94,    95,    96,   207,    15,    99,
      17,   100,   101,   102,   103,   104,     0,    15,    66,     3,
       4,    19,     6,     7,    14,    15,   116,   117,   118,   119,
     120,   121,   122,   123,    15,   198,    17,    15,    22,     3,
       4,    19,     6,     7,     8,   208,     3,     4,   108,     6,
       7,    47,    16,   216,   217,    18,   146,     3,     4,    20,
       6,     7,    21,   160,    18,    22,    43,     8,    45,    46,
      47,    17,    36,    37,    38,    16,    21,   182,   183,    43,
      20,   171,    46,    47,    48,    49,    50,     9,    10,    11,
      12,    13,   182,   183,   184,   200,    21,    38,     3,     4,
     205,     6,     7,    36,    37,    46,    47,    48,    49,    50,
     200,    47,    48,    49,    50,   205,    17,    38,    39,    40,
     210,    14,    15,   213,   184,     3,     4,    17,     6,     7,
       8,   102,   103,   104,   100,   101,    14,    41,    16,    18,
      18,    19,    45,    46,    22,    23,    42,    25,    26,    27,
      28,    29,    21,    14,    14,    17,    14,    16,    36,    37,
      38,    16,    16,    14,    17,    43,    14,    24,    46,    47,
      48,    49,    50,     3,     4,    14,     6,     7,     8,    14,
      17,    17,    74,   194,    14,     6,    16,   116,    18,    19,
      42,    38,    22,    23,   108,    25,    26,    27,    28,    29,
     117,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,
      50,     3,     4,    -1,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    16,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    47,    48,    49,    50,     3,
       4,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    47,    48,    49,    50,     3,     4,    -1,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,     8,
      46,    47,    48,    49,    50,    14,    -1,    16,    -1,    18,
      -1,    -1,    -1,    -1,    23,     8,    25,    26,    27,    28,
      29,    -1,    -1,    16,    17,    -1,    -1,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    -1,     8,    46,    47,    48,    49,    50,    14,    -1,
      16,    30,    31,    32,    33,    34,    35,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    47,    48,    49,    50,    36,    37,    38,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,    22,    52,    53,    63,    64,
      68,    71,    53,     0,    63,    71,     8,    38,    46,    59,
      60,    61,    62,    69,    70,    60,    61,    65,    66,    60,
      60,     9,    16,    20,    72,     9,    20,    14,    15,     9,
       9,    14,    15,     8,    16,    36,    37,    38,    43,    46,
      47,    48,    49,    50,    54,    55,    56,    57,    58,    85,
      87,    88,    89,    90,    47,    17,    53,    73,    74,    18,
      47,    60,    70,    54,    18,    66,    56,    85,    86,    92,
      93,    94,    95,    55,    56,    90,    90,    56,    85,    86,
       9,    10,    11,    12,    13,    16,    20,    44,    45,    20,
      36,    37,    38,    39,    40,    21,    18,    60,    15,    17,
      54,    67,    21,    67,    17,    17,    42,    41,    30,    31,
      32,    33,    34,    35,    85,    85,    85,    85,    85,    17,
      85,    91,    85,    85,    88,    88,    89,    89,    89,    14,
      18,    23,    25,    26,    27,    28,    29,    53,    63,    75,
      76,    78,    79,    81,    82,    83,    84,    85,    74,    18,
      15,    19,    19,    92,    93,    94,    85,    85,    94,    85,
      85,    15,    17,    21,    21,    14,    14,    14,    85,    78,
      19,    79,    16,    16,    16,    14,    78,    54,    85,    14,
      19,    77,    86,    86,    53,    85,    19,    17,    17,    69,
      14,    18,    80,    81,    80,    14,    86,    78,    24,    86,
      14,    19,    80,    14,    85,    85,    17,    17,    80,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    52,    52,    53,    53,    53,    53,
      54,    54,    54,    54,    55,    55,    56,    56,    56,    57,
      57,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    63,    64,    65,    65,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    70,    71,    71,    72,    73,    73,
      74,    75,    76,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    83,    84,    85,    85,    85,    85,    85,
      85,    86,    87,    87,    87,    88,    88,    88,    88,    89,
      89,    89,    89,    89,    89,    90,    90,    90,    90,    90,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    94,
      95,    95,    95,    95,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       4,     1,     1,     1,     1,     2,     2,     4,     4,     1,
       1,     1,     4,     1,     3,     3,     5,     1,     3,     3,
       1,     3,     1,     3,     5,     8,     7,     1,     1,     3,
       2,     3,     1,     1,     1,     2,     1,     1,     3,     1,
       1,     2,     1,     7,     5,     5,    10,     9,     2,     2,
       2,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     2,     2,     1,     3,     3,     4,     3,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 59 "src/parser.y" /* yacc.c:1646  */
    {root->addChild((yyvsp[0]));}
#line 1494 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 60 "src/parser.y" /* yacc.c:1646  */
    {root->addChild((yyvsp[0]));}
#line 1500 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 61 "src/parser.y" /* yacc.c:1646  */
    {root->addChild((yyvsp[0]));}
#line 1506 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 62 "src/parser.y" /* yacc.c:1646  */
    {root->addChild((yyvsp[0]));}
#line 1512 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 68 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_INT;}
#line 1518 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 69 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_CHAR;}
#line 1524 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 70 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_BOOL;}
#line 1530 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 71 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_VOID;}
#line 1536 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 75 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[0]));}
#line 1542 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 76 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[0]));}
#line 1548 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 77 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[0]));}
#line 1554 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 78 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[0]));}
#line 1560 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1566 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = (yyvsp[0]);
	// 归约完成，清除下标计数器，为下一次做准备
	(yyval)->child->type->visitDim = 0;
  }
#line 1576 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 93 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode((yyvsp[0]));}
#line 1582 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 94 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); (yyval)->pointLevel++;}
#line 1588 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 95 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = (yyvsp[0]); 
	(yyval)->pointLevel--;
	if ((yyval)->pointLevel < -2) {
		yyerror("Continuous addr operator");
	}
  }
#line 1600 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 106 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_INDEX;
	(yyval)->addChild((yyvsp[-3]));

	// 计算数组偏移量倍数
	int biasRate = 1;
	for (unsigned int i = (yyvsp[-3])->type->visitDim + 1; i < (yyvsp[-3])->type->dim; i++) {
		biasRate *= (yyvsp[-3])->type->dimSize[i];
	}
	TreeNode* biasNode;
	if (biasRate == 1) {
		// 偏移倍数为1时省略乘法结点
		biasNode = (yyvsp[-1]);
	}
	else {
		biasNode = new TreeNode(lineno, NODE_OP);
		biasNode->optype = OP_MUL;
		biasNode->addChild((yyvsp[-1]));
		TreeNode* biasRateExpr = new TreeNode(lineno, NODE_EXPR);
		TreeNode* biasRateConst = new TreeNode(lineno, NODE_CONST);
		biasRateConst->type = TYPE_INT;
		biasRateConst->int_val = biasRate;
		biasRateExpr->addChild(biasRateConst);
		biasNode->addChild(biasRateExpr);
	}
	(yyvsp[-3])->type->visitDim++;

	(yyval)->addChild(biasNode);
  }
#line 1635 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 136 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = (yyvsp[-3]);
	TreeNode* newBiasNode = new TreeNode(lineno, NODE_OP);
	newBiasNode->optype = OP_ADD;
	newBiasNode->addChild((yyval)->child->sibling);
	(yyval)->child->sibling = newBiasNode;

	// 计算数组偏移量倍数
	int biasRate = 1;
	for (unsigned int i = (yyval)->child->type->visitDim + 1; i < (yyval)->child->type->dim; i++) {
		biasRate *= (yyval)->child->type->dimSize[i];
	}

	TreeNode* biasNode;
	if (biasRate == 1) {
		// 偏移倍数为1时省略乘法结点
		biasNode = (yyvsp[-1]);
	}
	else {
		biasNode->optype = OP_MUL;
		biasNode->addChild((yyvsp[-1]));
		TreeNode* biasRateExpr = new TreeNode(lineno, NODE_EXPR);
		TreeNode* biasRateConst = new TreeNode(lineno, NODE_CONST);
		biasRateConst->type = TYPE_INT;
		biasRateConst->int_val = biasRate;
		biasRateExpr->addChild(biasRateConst);
		biasNode->addChild(biasRateExpr);
	}
	(yyval)->child->type->visitDim++;
	newBiasNode->addChild(biasNode);
  }
#line 1671 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 170 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = (yyvsp[0]);
	int idNameCount = idNameList.count((yyval)->var_name);
	int declCnt = 0;
	int minDefDis = MAX_SCOPE_STACK;

	// 搜索变量是否已经声明
	auto it = idNameList.find((yyval)->var_name);
	int resScoptCmp;
	while (idNameCount--) {
		resScoptCmp = scopeCmp(presentScope, it->second);
		if (resScoptCmp >= 0){
			// 寻找最近的定义
			if (resScoptCmp < minDefDis) {
				minDefDis = resScoptCmp;
				(yyval) = idList[make_pair(it->first, it->second)];
			}
			declCnt++;
		}
		it++;
	}
	if (declCnt == 0) {
		string t = "Undeclared identifier :'" + (yyvsp[0])->var_name + "', scope : " + to_string(resScoptCmp);
		yyerror(t.c_str());
	}
}
#line 1702 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 199 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1708 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 200 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1714 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1720 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 205 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); (yyval)->type->pointLevel++;}
#line 1726 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 206 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); (yyval)->type->pointLevel--;}
#line 1732 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 211 "src/parser.y" /* yacc.c:1646  */
    {
  (yyval) = (yyvsp[-3]);
  (yyval)->type->type = VALUE_ARRAY;
  (yyval)->type->elementType = (yyvsp[-3])->type->type;
  (yyval)->type->dimSize[(yyval)->type->dim] = (yyvsp[-1])->int_val;
  (yyval)->type->dim++;
}
#line 1744 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 218 "src/parser.y" /* yacc.c:1646  */
    {
  (yyval) = (yyvsp[-3]);
  (yyval)->type->dimSize[(yyval)->type->dim] = (yyvsp[-1])->int_val;
  (yyval)->type->dim++;
}
#line 1754 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 226 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = (yyvsp[0]);
	(yyval)->var_scope = presentScope;
	(yyval)->type = new Type(NOTYPE);
	#ifdef ID_REDUCE_DEBUG
		cout<<"# $ reduce declIdentifier : "<<(yyval)->var_name<<", at scope :"<<presentScope<<endl;
	#endif
	if (idList.count(make_pair((yyval)->var_name, (yyval)->var_scope)) != 0) {
		string t = "Redeclared identifier : " + (yyval)->var_name;
		yyerror(t.c_str());
	}
	idNameList.insert(make_pair((yyval)->var_name, (yyval)->var_scope));
	idList[make_pair((yyval)->var_name, (yyval)->var_scope)] = (yyval);
}
#line 1773 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 245 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1779 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 246 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1785 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 250 "src/parser.y" /* yacc.c:1646  */
    {
  (yyval) = new TreeNode(lineno, NODE_STMT);
  (yyval)->stype = STMT_CONSTDECL;
  (yyval)->type = TYPE_NONE;
  (yyval)->addChild((yyvsp[-2]));
  (yyval)->addChild((yyvsp[-1]));  
  TreeNode* p = (yyvsp[-1])->child;
  while(p != nullptr) {
	  p->child->type->copy((yyvsp[-2])->type);
	  p->child->type->constvar = true;
	  p = p->sibling;
  }
}
#line 1803 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 266 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[0]));}
#line 1809 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 267 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); (yyval)->addChild((yyvsp[0]));}
#line 1815 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 271 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP); 
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[-2])); 
	(yyval)->addChild((yyvsp[0]));
  }
#line 1826 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 277 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[-4])); 
	(yyval)->addChild((yyvsp[-1]));
  }
#line 1837 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 287 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[0]));}
#line 1843 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 288 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); (yyval)->addChild((yyvsp[0]));}
#line 1849 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 292 "src/parser.y" /* yacc.c:1646  */
    {
  (yyval) = new TreeNode(lineno, NODE_STMT);
  (yyval)->stype = STMT_DECL;
  (yyval)->type = TYPE_NONE;
  (yyval)->addChild((yyvsp[-2]));
  (yyval)->addChild((yyvsp[-1]));
  TreeNode* p = (yyvsp[-1])->child;
  while(p != nullptr) {
	  if (p->nodeType == NODE_OP) {
		  p->child->type->copy((yyvsp[-2])->type);
	  }
	  else {
	  	p->type->copy((yyvsp[-2])->type);
	  }
	  p = p->sibling;
  }
  #ifdef DECL_DEBUG
	cout << "# $ reduce varDecl type = " << (yyvsp[-2])->type->getTypeInfo() << endl;
	// $$->printAST();
  #endif
}
#line 1875 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 317 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[0]));}
#line 1881 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 318 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); (yyval)->addChild((yyvsp[0]));}
#line 1887 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 322 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1893 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 323 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
  }
#line 1904 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 329 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[-4]));
	(yyval)->addChild((yyvsp[-1]));
  }
#line 1915 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 340 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FUNCDECL;
	(yyvsp[-6])->type->type = COMPOSE_FUNCTION;
	TreeNode* param = (yyvsp[-4]);
	while (param != nullptr) {
		(yyvsp[-6])->type->paramType[(yyvsp[-6])->type->paramNum] = param->child->type;
		(yyvsp[-6])->type->paramNum++;
		param = param->sibling;
	}
	(yyvsp[-6])->type->retType = (yyvsp[-7])->type;
	(yyval)->addChild((yyvsp[-7]));
	(yyval)->addChild((yyvsp[-6]));
	TreeNode* params = new TreeNode(lineno, NODE_VARLIST);
	params->addChild((yyvsp[-4]));
	(yyval)->addChild(params);
	TreeNode* funcBlock = new TreeNode(lineno, NODE_STMT);
	funcBlock->stype = STMT_BLOCK;
	funcBlock->addChild((yyvsp[-1]));
	(yyval)->addChild(funcBlock);
	scopePop();
  }
#line 1942 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 362 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FUNCDECL;
	(yyvsp[-5])->type->type = COMPOSE_FUNCTION;
	(yyvsp[-5])->type->retType = (yyvsp[-6])->type;
	(yyval)->addChild((yyvsp[-6]));
	(yyval)->addChild((yyvsp[-5]));
	(yyval)->addChild(new TreeNode(lineno, NODE_VARLIST));
	TreeNode* funcBlock = new TreeNode(lineno, NODE_STMT);
	funcBlock->stype = STMT_BLOCK;
	funcBlock->addChild((yyvsp[-1]));
	(yyval)->addChild(funcBlock);
	scopePop();
  }
#line 1961 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 378 "src/parser.y" /* yacc.c:1646  */
    {scopePush();}
#line 1967 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 381 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1973 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 382 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); (yyval)->addSibling((yyvsp[0]));}
#line 1979 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 386 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_PARAM); 
	(yyval)->addChild((yyvsp[-1])); 
	(yyval)->addChild((yyvsp[0]));
	(yyvsp[0])->type->copy((yyvsp[-1])->type);
  }
#line 1990 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 397 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_BLOCK;
	(yyval)->addChild((yyvsp[-1]));
}
#line 2000 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 403 "src/parser.y" /* yacc.c:1646  */
    {scopePush();}
#line 2006 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 404 "src/parser.y" /* yacc.c:1646  */
    {scopePop();}
#line 2012 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 407 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2018 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 408 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]); (yyval)->addSibling((yyvsp[0]));}
#line 2024 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 412 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2030 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 413 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2036 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 417 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_BLOCK;
	(yyval)->addChild((yyvsp[-1]));
  }
#line 2046 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 422 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2052 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 426 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_STMT); (yyval)->stype = STMT_SKIP;}
#line 2058 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 427 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2064 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 428 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2070 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 429 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_IFELSE;
	(yyval)->addChild((yyvsp[-4]));
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
	scopePop();
	#ifdef IFELSE_DEBUG
		cout << "# $ reduce IF-ELSE at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
#line 2086 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 440 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_IF;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
	scopePop();
	#ifdef IF_DEBUG
		cout << "% # $ reduce IF at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
#line 2101 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 450 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_WHILE;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
	inCycle = false;
	scopePop();
	#ifdef WHILE
		cout << "# $ reduce WHILE at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
#line 2117 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 461 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FOR;
	TreeNode* forDecl = new TreeNode(lineno, NODE_STMT);
	forDecl->stype = STMT_DECL;
	forDecl->addChild((yyvsp[-7]));
	TreeNode* p = (yyvsp[-6])->child;
	while (p) {
		if (p->nodeType == NODE_OP) {
			p->child->type->copy((yyvsp[-7])->type);
		}
		else {
			p->type->copy((yyvsp[-7])->type);
		}
		p = p->sibling;
	}
	forDecl->addChild((yyvsp[-6]));
	(yyval)->addChild(forDecl);
	(yyval)->addChild((yyvsp[-4]));
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
	inCycle = false;
	scopePop();
  }
#line 2146 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 485 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FOR;
	(yyval)->addChild((yyvsp[-6]));
	(yyval)->addChild((yyvsp[-4]));
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
	inCycle = false;
	scopePop();
  }
#line 2161 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 496 "src/parser.y" /* yacc.c:1646  */
    {
	if (!inCycle) {
		yyerror("break statement outside loop");
	}
	(yyval) = new TreeNode(lineno, NODE_STMT); 
	(yyval)->stype = STMT_BREAK; 
	(yyval)->type = TYPE_NONE;
  }
#line 2174 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 504 "src/parser.y" /* yacc.c:1646  */
    {
	if (!inCycle) {
		yyerror("continue statement outside loop");
	}
	(yyval) = new TreeNode(lineno, NODE_STMT); 
	(yyval)->stype = STMT_CONTINUE; 
	(yyval)->type = TYPE_NONE;
  }
#line 2187 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 512 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_STMT); (yyval)->stype = STMT_RETURN; (yyval)->type = TYPE_NONE;}
#line 2193 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 513 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_STMT); (yyval)->stype = STMT_RETURN; (yyval)->addChild((yyvsp[-1])); (yyval)->type = TYPE_NONE;}
#line 2199 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 516 "src/parser.y" /* yacc.c:1646  */
    {scopePush();}
#line 2205 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 517 "src/parser.y" /* yacc.c:1646  */
    {inCycle = true; scopePush();}
#line 2211 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 518 "src/parser.y" /* yacc.c:1646  */
    {inCycle = true; scopePush();}
#line 2217 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 523 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2223 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 524 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_ASSIGN;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
	#ifdef ASSIGN_DEBUG
		cout << "# $ reduce ASSIGN at scope : " << presentScope << ", at line " << lineno << endl;
		// $$->printAST();
	#endif
  }
#line 2238 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 534 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_ADDASSIGN;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
  }
#line 2249 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 540 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_SUBASSIGN;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
  }
#line 2260 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 546 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_MULASSIGN;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
  }
#line 2271 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 552 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DIVASSIGN;
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild((yyvsp[0]));
  }
#line 2282 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 561 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2288 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 565 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2294 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 566 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_ADD; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2300 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 567 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_SUB; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2306 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 572 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2312 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 573 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_MUL; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2318 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 574 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_DIV; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2324 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 575 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_MOD; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2330 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 580 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2336 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 581 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_NOT; (yyval)->addChild((yyvsp[0]));}
#line 2342 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 582 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_POS; (yyval)->addChild((yyvsp[0]));}
#line 2348 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 583 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_NAG; (yyval)->addChild((yyvsp[0]));}
#line 2354 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 584 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_INC; (yyval)->addChild((yyvsp[-1]));}
#line 2360 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 585 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_DEC; (yyval)->addChild((yyvsp[-1]));}
#line 2366 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 590 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2372 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 591 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2378 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 592 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2384 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 593 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_FUNCALL);
	(yyval)->addChild((yyvsp[-3]));
	(yyval)->addChild((yyvsp[-1]));
	#ifdef FUNCALL_DEBUG
		cout << "# $ reduce function call at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
#line 2397 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 601 "src/parser.y" /* yacc.c:1646  */
    {
	(yyval) = new TreeNode(lineno, NODE_FUNCALL);
	(yyval)->addChild((yyvsp[-2]));
	(yyval)->addChild(new TreeNode(lineno, NODE_VARLIST));
	#ifdef FUNCALL_DEBUG
		cout << "# $ reduce function call at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  }
#line 2410 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 609 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[0]));}
#line 2416 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 614 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[0]));}
#line 2422 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 615 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-2]); (yyval)->addChild((yyvsp[0]));}
#line 2428 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 620 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2434 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 621 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_OR; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2440 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 626 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2446 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 627 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_AND; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2452 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 632 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2458 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 633 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_EQ; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2464 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 634 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_NEQ; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2470 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 639 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2476 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 640 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_GRA; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2482 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 641 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_LES; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2488 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 642 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_GRAEQ; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2494 "src/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 643 "src/parser.y" /* yacc.c:1646  */
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_LESEQ; (yyval)->addChild((yyvsp[-2])); (yyval)->addChild((yyvsp[0]));}
#line 2500 "src/parser.cpp" /* yacc.c:1646  */
    break;


#line 2504 "src/parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 646 "src/parser.y" /* yacc.c:1906  */


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
