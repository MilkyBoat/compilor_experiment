#include "type.h"

Type::Type(ValueType valueType) {
    this->type = valueType;
    this->paramNum = 0;
    constvar = false;
    this->retType = nullptr;
    this->dim = 0;
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
    int size = 0;
    int eleSize;
    switch (type)
    {
    case VALUE_BOOL:
    case VALUE_INT:
    case VALUE_CHAR:
    case VALUE_STRING:
        return 4;
    case VALUE_ARRAY:
        this->type = elementType;
        eleSize = this->getSize();
        this->type = VALUE_ARRAY;
        for (unsigned int i = 0; i < dim; i++)
            size += eleSize * dimSize[i];
        return size;
    default:
        return 0;
    }
}
