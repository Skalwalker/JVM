#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::fstore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_0(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_1(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_2(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_3(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::istore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = val;

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

uint32_t Instruction::lstore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;
    frame->localVariables[4] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type value;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = value;
    frame->localVariables[index+1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;
    frame->localVariables[4] = val;

    return ++frame->local_pc;
}
