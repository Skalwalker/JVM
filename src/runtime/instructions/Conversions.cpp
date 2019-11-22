#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::i2d(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = (double)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::i2f(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::i2l(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::i2b(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_BYTE;
    res.type_byte = (int8_t)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::i2s(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_SHORT;
    res.type_short = (int16_t)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::i2c(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_CHAR;
    res.type_char = (uint8_t)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}
