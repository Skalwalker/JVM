#include "../../../include/runtime/instructions/Instruction.hpp"

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
