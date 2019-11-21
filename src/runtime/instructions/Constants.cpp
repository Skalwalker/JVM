#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::bipush(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    int8_t byte1 = bytecode[++frame->local_pc];
    Type res;
    res.tag = TAG_INT;
    res.type_int = byte1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
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
