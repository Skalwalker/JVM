#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::pop2(Frame* frame) {
    uint8_t value = frame->operandStack.top().tag;

    if (value == TAG_LONG || value == TAG_DOUBLE) {
        frame->operandStack.pop();
    } else {
        frame->operandStack.pop()
        frame->operandStack.pop()
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
