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

/**
A brief description on a single line, ended by a period or blank line.

@file
*/


/**
A brief description on a single line, ended by a period or blank line.

A longer comment, which may stretch over several lines and may include other things like:
- a list like this
- special markup like below
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
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

uint32_t Instruction::i2f(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_FLOAT;
    res.type_float = (float)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
A brief description on a single line, ended by a period or blank line.

A longer comment, which may stretch over several lines and may include other things like:
- a list like this
- special markup like below
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
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

uint32_t Instruction::i2l(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;

    frame->operandStack.pop();

    Type res;
    res.tag = TAG_LONG;
    res.type_long = (long)value;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
A brief description on a single line, ended by a period or blank line.

A longer comment, which may stretch over several lines and may include other things like:
- a list like this
- special markup like below
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
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

uint32_t Instruction::i2b(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_BYTE;
    res.type_byte = (int8_t)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
A brief description on a single line, ended by a period or blank line.

A longer comment, which may stretch over several lines and may include other things like:
- a list like this
- special markup like below
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
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

uint32_t Instruction::i2s(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_SHORT;
    res.type_short = (int16_t)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
A brief description on a single line, ended by a period or blank line.

A longer comment, which may stretch over several lines and may include other things like:
- a list like this
- special markup like below
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
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


uint32_t Instruction::i2c(Frame* frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    Type res;
    res.tag = TAG_CHAR;
    res.type_char = (uint8_t)value;

    frame->operandStack.push(res);

    return ++frame->local_pc;
}

/**
A brief description on a single line, ended by a period or blank line.

A longer comment, which may stretch over several lines and may include other things like:
- a list like this
- special markup like below
@param myParam1 Description of 1st parameter.
@param myParam2 Description of 2nd parameter.
@returns Description of returned value.
*/
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
