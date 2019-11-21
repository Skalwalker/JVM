#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::lstore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type value;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = value;
    frame->localVariables[index+1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}
