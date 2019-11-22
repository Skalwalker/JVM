#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::f2d(Frame * frame){
    float val1;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = (double)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::f2i(Frame * frame){
    float val1;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int32_t)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::f2l(Frame * frame){
    float val1;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::d2f(Frame * frame){
    double val1;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::d2i(Frame * frame){
    double val1;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int32_t)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::d2l(Frame * frame){
    double val1;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)val1;;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}
