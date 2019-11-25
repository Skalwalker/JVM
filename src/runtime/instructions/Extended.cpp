#include "../../../include/runtime/instructions/Instruction.hpp"

// uint32_t Instruction::wide(Frame* frame){
//     uint8_t* bytecode = frame->codeAttribute.code;
//     uint8_t byte1 = bytecode[++frame->local_pc];
//     uint8_t byte2 = bytecode[++frame->local_pc];
// }
//
// uint32_t Instruction::multianewarray(Frame* frame){
//     uint8_t* bytecode = frame->codeAttribute.code;
//     uint8_t byte1 = bytecode[++frame->local_pc];
//     uint8_t byte2 = bytecode[++frame->local_pc];
//     uint8_t dimensions = bytecode[++frame->local_pc];
//
// }

uint32_t Instruction::ifnull(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    Type val1;
    val1 = frame->operandStack.top();
    frame->operandStack.pop();

    if (val1.type_reference == (uint64_t)NULL) {
        int16_t offset = (byte1 << 8) | byte2;
        frame->local_pc += offset-2;

        return frame->local_pc;
    }

    return ++frame->local_pc;
}

uint32_t Instruction::ifnonnull(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    Type val1;
    val1 = frame->operandStack.top();
    frame->operandStack.pop();

    if (val1.type_reference != (uint64_t)NULL) {
        int16_t offset = (byte1 << 8) | byte2;
        frame->local_pc += offset-2;

        return frame->local_pc;
    }

    return ++frame->local_pc;

}

uint32_t Instruction::goto_w(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint8_t byte3 = bytecode[++frame->local_pc];
    uint8_t byte4 = bytecode[++frame->local_pc];

    int32_t offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    frame->local_pc += offset-2;

    return frame->local_pc;

}

uint32_t Instruction::jsr_w(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint8_t byte3 = bytecode[++frame->local_pc];
    uint8_t byte4 = bytecode[++frame->local_pc];

    Type res;
    res.tag = TAG_RETURN;
    res.type_returnAddress = ++frame->local_pc;

    frame->operandStack.push(res);

    int32_t offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    frame->local_pc += offset-2;

    return frame->local_pc;
}
