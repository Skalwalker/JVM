#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::newarray(Frame *frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t atype = bytecode[++frame->local_pc];
    int count = frame->operandStack.top().type_int;
    frame->operandStack.top();

    Type *arr_type = (Type*)malloc(count*(sizeof(Type)));

    Type *value;
    value = (Type*)malloc(sizeof(Type));

    if (atype == T_BOOLEAN) {
        value->tag = TAG_BOOL;
        value->type_boolean = false;
    } else if (atype == T_CHAR) {
        value->tag = TAG_CHAR;
        value->type_char = 0;
    }  else if (atype == T_FLOAT) {
        value->tag = TAG_FLOAT;
        value->type_float = 0.0f;
    }  else if (atype == T_DOUBLE) {
        value->tag = TAG_DOUBLE;
        value->type_double = 0.0;
    }  else if (atype == T_BYTE) {
        value->tag = TAG_BYTE;
        value->type_byte = 0;
    }  else if (atype == T_SHORT) {
        value->tag = TAG_SHORT;
        value->type_short = 0;
    }  else if (atype == T_INT) {
        value->tag = TAG_INT;
        value->type_int = 0;
    }  else if (atype == T_LONG) {
        value->tag = TAG_LONG;
        value->type_long = 0;
    }

    for (int i = 0; i < count; i++) {
        arr_type[i] = *value;
    }

    Type arrayReference;
    arrayReference.tag = TAG_REFERENCE;
    arrayReference.type_reference = (uint64_t)&arr_type[0];
    frame->operandStack.push(arrayReference);

    Type res = frame->operandStack.top();
    Type* arrayPointer = (Type*)(res.type_reference);

    return ++frame->local_pc;
}

uint32_t Instruction::getstatic(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string className = frame->constantPool[index-1].getInfo(frame->constantPool);

    if (className.compare("java/lang/System") != 0) {
        cout << "AQUI VAO ACONTECER MUITAS OUTRAS COISAS" << endl;
    }

    return ++frame->local_pc;
}


uint32_t Instruction::invokevirtual(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;


    string method = frame->constantPool[index-1].getInfo(frame->constantPool);
    int j = 0;
    int w = 0;


    while (w < method.size() && method[w+1] != '#') {
        w++;
    }
    string className = method.substr(0,w+1);
    string nameAndType = method.substr(w+2, method.size());
    while (j < nameAndType.size() && nameAndType[j+1] != '$') {
        j++;
    }
    string methodName = nameAndType.substr(0,j+1);
    string descriptor = nameAndType.substr(j+2,nameAndType.size());

    if (className.compare("java/io/PrintStream") == 0) {
        if (methodName.compare("println") == 0) {
            if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
                string* stringReference = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                cout << *stringReference << endl;
            } else if (descriptor.compare("(I)V") == 0){
                cout << frame->operandStack.top().type_int << endl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(J)V") == 0){
                cout << frame->operandStack.top().type_long << endl;
                frame->operandStack.pop();
            }
        }
    }
    return ++frame->local_pc;
}
