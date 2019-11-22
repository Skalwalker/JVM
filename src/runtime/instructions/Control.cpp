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
