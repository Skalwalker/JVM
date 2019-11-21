#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::returnfunc(Frame * frame) {
    return frame->local_pc;
}
