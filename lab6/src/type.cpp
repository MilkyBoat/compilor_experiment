#include "type.h"

Type::Type(ValueType valueType) {
    this->type = valueType;
    this->paramNum = 0;
    this->constvar = false;
    this->retType = nullptr;
    this->dim = 0;
    this->visitDim = 0;
}

void Type::copy(Type* a) {
    this->type = a->type;
    this->constvar = a->constvar;
    if (a->paramNum) {
        this->paramNum = a->paramNum;
        for (unsigned short i=0;i<a->paramNum;i++) {
            this->paramType[i] = a->paramType[i];
        }
        this->retType = a->retType;
    }
    if (a->dim) {
        this->dim = a->dim;
        this->elementType = a->elementType;
        for (unsigned int i=0;i<a->dim;i++) {
            this->dimSize[i] = a->dimSize[i];
        }
    }
}

string Type::getTypeInfo() {
    return getTypeInfo(this->type);
}

string Type::getTypeInfo(ValueType type) {
    switch(type) {
        case VALUE_BOOL:
            return "bool";
        case VALUE_INT:
            return "int";
        case VALUE_CHAR:
            return "char";
        case VALUE_STRING:
            return "string";
        case VALUE_ARRAY:
            if (this->dim > 0) {
                string buf = getTypeInfo(this->elementType);
                for (unsigned int i = 0; i < dim && i < MAX_ARRAY_DIM; i++) {
                    buf += "[" + to_string(dimSize[i]) + "]";
                }
                return buf;
            }
            return "";
        case VALUE_VOID:
            return "void";
        case NOTYPE:
            return "no type";
        default:
            return "?";
    }
}

void Type::addParam(Type* param){
    this->paramType[paramNum++] = param;
}

void Type::addRet(Type* t){
    this->retType = t;
}

int Type::getSize() {
    int size = 1;
    int eleSize;
    switch (type)
    {
    case VALUE_BOOL:
    case VALUE_INT:
    case VALUE_CHAR:
    case VALUE_STRING:
        return 4;
    case VALUE_ARRAY:
        eleSize = 4;
        for (unsigned int i = 0; i < dim; i++)
            size *= dimSize[i];
        return eleSize * size;
    default:
        return 0;
    }
}
