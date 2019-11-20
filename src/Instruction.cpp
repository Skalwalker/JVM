#include "../include/Instruction.hpp"


Instruction::Instruction() { }

Instruction::Instruction(string opcode_name) {
    this->mnemonic = opcode_name;
}

Instruction::Instruction(string opcode_name, uint32_t bytecount) {
    this->mnemonic = opcode_name;
    this->bytecount = bytecount;
}

uint32_t Instruction::getstatic(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string className = frame->constantPool[index-1].getInfo(frame->constantPool);
    if (className.compare("java/lang/System") == 0) {
        return ++frame->local_pc;
    }
}

uint32_t Instruction::ldc(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte = bytecode[++frame->local_pc];
    uint8_t index = byte;
    Type value;

    CPInfo cpInfo = frame->constantPool[index-1];
    if(cpInfo.tag == 8) {
        value.type_reference = (uint64_t)new string(cpInfo.getInfo(frame->constantPool));
        // value.tag = CAT1;
        frame->operandStack.push(value);
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
            }
        }
    }
    return ++frame->local_pc;
}

uint32_t Instruction::returnfunc(Frame * frame) {
    return frame->local_pc;
}
