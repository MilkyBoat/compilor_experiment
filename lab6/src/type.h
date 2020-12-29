#ifndef TYPESYSTEM_H
#define TYPESYSTEM_H
#include "./pch.h"
using namespace std;

#define MAX_PARAM 16
#define MAX_ARRAY_DIM 8
#define MAX_SCOPE_STACK 32
#define SCOPT_ID_BASE '1'

#define EXIT_AT_GRAMMA_ERROR

#define AST
// #define DEBUG
#ifdef DEBUG
// #define SCOPE_DEBUG
// #define ID_TOKEN_DEBUG
// #define ID_REDUCE_DEBUG
#define DECL_DEBUG
// #define POINT_DEBUG
#define ASSIGN_DEBUG
// #define IF_DEBUG
// #define IFELSE_DEBUG
// #define WHILE_DEBUG
// #define FUNCALL_DEBUG
#define typeCheck_debug
#endif

enum ValueType
{
    NOTYPE,
    VALUE_BOOL,
    VALUE_INT,
    VALUE_CHAR,
    VALUE_STRING,
    VALUE_VOID,
    VALUE_ARRAY,
    COMPOSE_FUNCTION
};

class Type
{
public:
    bool constvar;
    ValueType type;
    Type(ValueType valueType);

public:  

    unsigned short paramNum; // for function
    Type* paramType[MAX_PARAM];
    Type* retType;
    void addParam(Type* t);
    void addRet(Type* t);
 
    unsigned int dim;   // for array
    ValueType elementType;
    int dimSize[MAX_ARRAY_DIM];

    int getSize();

public:
    ValueType* sibling; 
public:
    string getTypeInfo();
    string getTypeInfo(ValueType type);
};

// 设置几个常量Type，可以节省空间开销
static Type* TYPE_INT = new Type(VALUE_INT);
static Type* TYPE_CHAR = new Type(VALUE_CHAR);
static Type* TYPE_BOOL = new Type(VALUE_BOOL);
static Type* TYPE_STRING = new Type(VALUE_STRING);
static Type* TYPE_VOID = new Type(VALUE_VOID);
static Type* TYPE_NONE = new Type(NOTYPE);

int getSize(Type* type);

#endif