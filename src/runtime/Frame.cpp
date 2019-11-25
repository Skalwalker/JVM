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
        this->localVariables = vector<Type>(maxLocals);
        this->local_pc = 0;
    }
    else {
        printf("Atributo Code nao encontrado no metodo\n");
        exit(0);
    }
}
