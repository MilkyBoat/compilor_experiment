#include "type.h"

Type::Type(ValueType valueType) {
    this->type = valueType;
    this->paramNum = 0;
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
