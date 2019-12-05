/** \file Stack.cpp
 * \brief Definições das instruções de Stack declaradas em Instruction.
 *
 * Referente às instruções definidas em Instruction.hpp do tipo Stack da Java SE 8 Edition.
 * Instruções do tipo Stack realizam operações de pilha, como pop e push.
 *
 * \date Date: 29/11/2019
 */

#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::pop2(Frame* frame) {
    uint8_t value = frame->operandStack.top().tag;

    if (value == TAG_LONG || value == TAG_DOUBLE) {
        frame->operandStack.pop();
    } else {
        frame->operandStack.pop();
        frame->operandStack.pop();
    }

    return ++frame->local_pc;
}

uint32_t Instruction::dup2(Frame* frame) {
    Type value1 = frame->operandStack.top();

    if (value1.tag == TAG_LONG || value1.tag == TAG_DOUBLE) {
        frame->operandStack.push(value1);
    } else {
        frame->operandStack.pop();
        Type value2 = frame->operandStack.top();
        frame->operandStack.push(value1);
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::dup2_x1(Frame* frame) {
    Type value1 = frame->operandStack.top();
    frame->operandStack.pop();
    Type value2 = frame->operandStack.top();

    if ((value1.tag == TAG_LONG || value1.tag == TAG_DOUBLE) &&
        (value2.tag != TAG_LONG && value2.tag != TAG_DOUBLE)) {
        frame->operandStack.pop();
        frame->operandStack.push(value1);
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
    } else {
        frame->operandStack.pop();
        Type value3 = frame->operandStack.top();
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
        frame->operandStack.push(value3);
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::dup2_x2(Frame* frame) {
    Type value1 = frame->operandStack.top();
    frame->operandStack.pop();
    Type value2 = frame->operandStack.top();
    frame->operandStack.pop();
    Type value3 = frame->operandStack.top();

    if ((value1.tag == TAG_LONG || value1.tag == TAG_DOUBLE) &&
        (value2.tag == TAG_LONG || value2.tag == TAG_DOUBLE)) {
        frame->operandStack.push(value1);
    } else if ((value1.tag != TAG_LONG && value1.tag != TAG_DOUBLE) &&
               (value2.tag != TAG_LONG && value2.tag != TAG_DOUBLE) &&
               (value3.tag == TAG_LONG && value3.tag == TAG_DOUBLE)) {
        frame->operandStack.pop();
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
        frame->operandStack.push(value3);
    } else if ((value1.tag == TAG_LONG || value1.tag == TAG_DOUBLE) &&
               (value2.tag != TAG_LONG && value2.tag != TAG_DOUBLE) &&
               (value3.tag != TAG_LONG && value3.tag != TAG_DOUBLE)) {
        frame->operandStack.pop();
        frame->operandStack.push(value1);
        frame->operandStack.push(value3);
    } else {
        frame->operandStack.pop();
        Type value4 = frame->operandStack.top();
        frame->operandStack.pop();
        frame->operandStack.push(value2);
        frame->operandStack.push(value1);
        frame->operandStack.push(value4);
        frame->operandStack.push(value3);
    }
    frame->operandStack.push(value2);
    frame->operandStack.push(value1);

    return ++frame->local_pc;
}

uint32_t Instruction::pop(Frame * frame) {
    frame->operandStack.pop();
    return ++frame->local_pc;
}

uint32_t Instruction::dup(Frame * frame) {
    Type res = frame->operandStack.top();
    frame->operandStack.push(res);
    return ++frame->local_pc;
}

uint32_t Instruction::dup_x1(Frame * frame) {
    Type res = frame->operandStack.top();
    Type d1 = frame->operandStack.top();
    frame->operandStack.pop();
    Type d2 = frame->operandStack.top();
    frame->operandStack.pop();
    frame->operandStack.push(res);
    frame->operandStack.push(d2);
    frame->operandStack.push(d1);
    return ++frame->local_pc;
}

uint32_t Instruction::dup_x2(Frame * frame) {
    Type new_val = frame->operandStack.top();
    Type val1 = frame->operandStack.top();
    frame->operandStack.pop();
    Type val2 = frame->operandStack.top();
    frame->operandStack.pop();

    if (val2.tag == TAG_LONG || val2.tag == TAG_DOUBLE) {
        frame->operandStack.push(new_val);
    } else {
        Type val3 = frame->operandStack.top();
        frame->operandStack.pop();
        frame->operandStack.push(new_val);
        frame->operandStack.push(val3);
    }

    frame->operandStack.push(val2);
    frame->operandStack.push(val1);

    return ++frame->local_pc;
}

uint32_t Instruction::swap(Frame * frame) {
    Type res1 = frame->operandStack.top();
    frame->operandStack.pop();
    Type res2 = frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(res1);
    frame->operandStack.push(res2);

    return ++frame->local_pc;
}
