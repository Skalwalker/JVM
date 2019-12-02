/**
 * \file Conversions.cpp
 * \brief Definições das instruções de conversão declaradas em Instruction.
 *
 * Referente às instruções definidas em Instruction.hpp do tipo Conversion da Java SE 8 Edition.
 * Instruções do tipo Conversion realizam a conversão de tipos, exemplo: inteiro para double. Elas
 * são dividas em duas categorias:
 * - Widening numeric conversion instructions: Instruction::i2l, Instruction::i2f, Instruction::i2d,
 * Instruction::l2f, Instruction::l2d, e Instruction::f2d
 * - Narrowing numeric conversions instructions: Instruction::i2b, Instruction::i2c, Instruction::i2s,
 * Instruction::l2i, Instruction::f2i, Instruction::f2l, Instruction::d2i, Instruction::d2l, e Instruction::d2f
 *
 * \date Date: 29/11/2019
 */

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
    res.tag = TAG_INT;
    res.type_int = (int32_t)((int8_t)value);

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::i2s(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int32_t)((int16_t)value);

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

uint32_t Instruction::l2i(Frame * frame){
    long val1;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_INT;
    res.type_int = (int)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::l2f(Frame * frame){
    long val1;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::l2d(Frame * frame){
    long val1;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_DOUBLE;
    res.type_double = (double)val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

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
