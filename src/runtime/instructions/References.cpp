#include "../../../include/runtime/instructions/Instruction.hpp"

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
                Type value = frame->operandStack.top();
                if (value.tag == TAG_INT) {
                    cout << frame->operandStack.top().type_int << endl;
                } else if (value.tag == TAG_SHORT) {
                    cout << frame->operandStack.top().type_short << endl;
                } else if (value.tag == TAG_BYTE) {
                    cout << (int32_t)frame->operandStack.top().type_byte << endl;
                }
                frame->operandStack.pop();
            } else if (descriptor.compare("(J)V") == 0){
                cout << frame->operandStack.top().type_long << endl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(F)V") == 0){
                printf("%f\n", frame->operandStack.top().type_float);
                frame->operandStack.pop();
            } else if (descriptor.compare("(D)V") == 0){
                printf("%f\n",frame->operandStack.top().type_double);
                frame->operandStack.pop();
            } else if (descriptor.compare("(C)V") == 0){
                int c = (int32_t)(frame->operandStack.top().type_char);
                if (isprint(c)) {
                    printf("%c\n", (char)(frame->operandStack.top().type_char));
                } else {
                    cout << "Non-Printable-Char: " << (int)c << endl;
                }
                frame->operandStack.pop();
            }
        }
    }
    return ++frame->local_pc;
}