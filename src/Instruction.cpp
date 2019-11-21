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
    if(cpInfo.tag == CONSTANT_STRING) {
        value.type_reference = (uint64_t)new string(cpInfo.getInfo(frame->constantPool));
        // value.tag = CAT1;
        frame->operandStack.push(value);
    } else if (cpInfo.tag == CONSTANT_INTEGER) {
        value.type_int = cpInfo.integerInfo.bytes;
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
            } else if (descriptor.compare("(I)V") == 0){
                cout << frame->operandStack.top().type_int << endl;
                frame->operandStack.pop();
            }
        }
    }
    return ++frame->local_pc;
}

uint32_t Instruction::returnfunc(Frame * frame) {
    return frame->local_pc;
}


uint32_t Instruction::iconst_m1(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = -1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iconst_0(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = 0;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iconst_1(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = 1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iconst_2(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = 2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iconst_3(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = 3;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iconst_4(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = 4;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iconst_5(Frame * frame){
    Type res;
    res.tag = TAG_INT;
    res.type_int = 5;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}


/* */
uint32_t Instruction::bipush(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    int8_t byte1 = bytecode[++frame->local_pc];
    Type res;
    res.tag = TAG_INT;
    res.type_int = byte1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}


uint32_t Instruction::istore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}


uint32_t Instruction::iload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

uint32_t Instruction::iload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

uint32_t Instruction::iload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

uint32_t Instruction::iload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


/* MAAAAAAATH */

uint32_t Instruction::iadd(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::isub(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}


uint32_t Instruction::imul(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}


uint32_t Instruction::idiv(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if(val2 == 0) {
        printf("TODO\n");
    } else {
        res.tag = TAG_INT;
        res.type_int = val1 / val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::irem(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if(val2 == 0) {
        printf("TODO\n");
    } else {
        res.tag = TAG_INT;
        res.type_int = val1 % val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::ineg(Frame * frame) {
    int32_t val1;
    Type res;
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ishl(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 << val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ishr(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iushr(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iand(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 & val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ior(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 | val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ixor(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

// uint32_t Instruction::iinc(Frame * frame) {
//     int32_t val1, val2;
//     Type res;
//     val1 = frame->operandStack.top().type_int;
//     frame->operandStack.top();
//     val2 = frame->operandStack.top().type_int;
//     frame->operandStack.pop();
//     res.tag = TAG_INT;
//     res.type_int = val1 + val2;
//     frame->operandStack.push(res);
// }
// uint32_t Instruction::fadd(Frame * frame) {
//
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fsub(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fmul(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fdiv(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::frem(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fneg(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dadd(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dsub(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dmul(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::ddiv(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::drem(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dneg(Frame * frame) {
//
//     return ++frame->local_pc;
// }
