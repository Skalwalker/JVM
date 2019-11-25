#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::nop(Frame * frame){
    return ++frame->local_pc;
}

uint32_t Instruction::aconst_null(Frame * frame){
    Type res;
    res.tag = TAG_REFERENCE;
    res.type_reference = (uint64_t)NULL;

    frame->operandStack.push(res);
    return ++frame->local_pc;
}

uint32_t Instruction::bipush(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    int8_t byte1 = bytecode[++frame->local_pc];
    Type res;
    res.tag = TAG_INT;
    res.type_int = byte1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::sipush(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    int32_t value = (byte1<<8) | byte2;
    Type res;
    res.tag = TAG_INT;
    res.type_int = (int32_t)value;
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
        value.tag = TAG_REFERENCE;
        value.type_reference = (uint64_t)new string(cpInfo.getInfo(frame->constantPool));
        // value.tag = CAT1;
        frame->operandStack.push(value);
    } else if (cpInfo.tag == CONSTANT_INTEGER) {
        value.tag = TAG_INT;
        value.type_int = cpInfo.integerInfo.bytes;
        frame->operandStack.push(value);
    } else if (cpInfo.tag == CONSTANT_FLOAT) {
        value.tag = TAG_FLOAT;
        float f;
        memcpy(&f, &(cpInfo.floatInfo.bytes), sizeof(float));
        value.type_float = f;
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

uint32_t Instruction::lconst_0(Frame * frame){
    Type res;
    res.tag = TAG_LONG;
    res.type_long = 0;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lconst_1(Frame * frame){
    Type res;
    res.tag = TAG_LONG;
    res.type_long = 1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::dconst_0(Frame * frame){
    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = 0.0;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::dconst_1(Frame * frame){
    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = 1.0;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fconst_0(Frame * frame){
    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = 0.0f;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fconst_1(Frame * frame){
    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = 1.0f;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fconst_2(Frame * frame){
    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = 2.0f;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}


uint32_t Instruction::ldc2_w(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    Type value;


    CPInfo cpInfo = frame->constantPool[index-1];
    if(cpInfo.tag == CONSTANT_LONG) {
        value.tag = TAG_LONG;
        long temp = (long)cpInfo.longInfo.high_bytes << 32;
        temp += cpInfo.longInfo.low_bytes;
        value.type_long = temp;
        frame->operandStack.push(value);
    } else if(cpInfo.tag == CONSTANT_DOUBLE) {
        value.tag = TAG_DOUBLE;
        uint32_t high, low;
        double res;
        high = cpInfo.doubleInfo.high_bytes;
        low = cpInfo.doubleInfo.low_bytes;
        uint32_t vec[2] = {low,high};
        memcpy(&res, vec, sizeof(double));
        value.type_double = res;
        frame->operandStack.push(value);
    }
    return ++frame->local_pc;
}

// uint32_t Instruction::ldc_w(Frame* frame){
//     uint8_t* bytecode = frame->codeAttribute.code;
//     uint8_t byte1 = bytecode[++frame->local_pc];
//     uint8_t byte2 = bytecode[++frame->local_pc];
//
//     uint16_t index = ((uint16_t)byte1 << 8) | byte2;
//
//     Type value;
//
//
//     CPInfo cpInfo = frame->constantPool[index-1];
//     if(cpInfo.tag == CONSTANT_INTEGER) {
//         value.tag = TAG_INT;
//
//
//     } else if(cpInfo.tag == CONSTANT_FLOAT) {
//         value.tag = TAG_FLOAT;
//
//     } else if(cpInfo.tag == CONSTANT_STRING) {
//         value.tag = TAG_REFERENCE;
//
//     } else if(cpInfo.tag == CONSTANT_CLASS) {
//
//     } else if(cpInfo.tag == CONSTANT_METHOD_TYPE) {
//
//     } else if(cpInfo.tag == CONSTANT_METHOD_HANDLE) {
//
//     }
//
// }
