#include "../../../include/runtime/instructions/Instruction.hpp"

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
