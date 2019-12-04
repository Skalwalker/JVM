#include "../../include/runtime/Frame.hpp"

Frame::Frame(vector<CPInfo> constantPool, MethodInfo method, stack<Frame>* jvmStack){
    uint16_t attributes_count = method.attributes_count;
    vector<AttributeInfo> attributes = method.attributes;

    this->constantPool = constantPool;
    this->method = method;
    this->jvmStack = jvmStack;

    bool codeFounded = false;
    // i tem que ser declaro aqui pois será usado fora do loop
    int i;
    for (i = 0; i < attributes_count && !codeFounded; i++) {
        AttributeInfo attribute = attributes[i];
        uint16_t nameIndex = attribute.attributeNameIndex;
        string attributeName = constantPool[nameIndex-1].getInfo(constantPool);

        if (attributeName.compare("Code") == 0) {
            codeFounded = true;
            i--;
        }
    }

    if (codeFounded) {
        uint16_t maxLocals = attributes[i].code.maxLocals;
        this->codeAttribute = attributes[i].code;
        this->localVariables = intializeLocalVariable(maxLocals);
        this->local_pc = 0;
    }
    else {
        printf("Atributo Code nao encontrado no metodo\n");
        exit(0);
    }
}

vector<Type> Frame::intializeLocalVariable(uint16_t maxLocals) {
    vector<Type> arr;
    vector<Type>* empty = new vector<Type>(0);
    for (int i = 0; i  < maxLocals; i++) {
        Type variable;
        variable.tag = TAG_REFERENCE;
        variable.type_reference = (uint64_t)empty;
        arr.push_back(variable);
    }

    return arr;
}
