#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::returnfunc(Frame * frame) {
    return frame->local_pc;
}

uint32_t Instruction::goto_func(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    int16_t offset;

    offset = (byte1 << 8) | byte2;

    frame->local_pc += offset-2;

    return frame->local_pc;
}

uint32_t Instruction::jsr(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    Type res;
    res.tag = TAG_RETURN;
    res.type_returnAddress = frame->local_pc;
    frame->operandStack.push(res);

    int16_t offset = (byte1 << 8) | byte2;
    frame->local_pc += offset-2;

    return frame->local_pc;
}

uint32_t Instruction::ret(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type res = frame->localVariables[index];

    return res.type_returnAddress;

}

// uint32_t Instruction::tableswitch(Frame * frame){
//
// }
//
// uint32_t Instruction::lookupswitch(Frame * frame){
//
// }
//
// uint32_t Instruction::ireturn(Frame * frame){
//
// }
//
// uint32_t Instruction::lreturn(Frame * frame){
//
// }
//
// uint32_t Instruction::freturn(Frame * frame){
//
// }
//
// uint32_t Instruction::dreturn(Frame * frame){
//
// }
//
// uint32_t Instruction::areturn(Frame * frame){
//
// }
