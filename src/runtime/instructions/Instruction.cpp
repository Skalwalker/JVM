#include "../../../include/runtime/instructions/Instruction.hpp"


Instruction::Instruction() { }

Instruction::Instruction(string opcode_name) {
    this->mnemonic = opcode_name;
}

Instruction::Instruction(string opcode_name, uint32_t bytecount) {
    this->mnemonic = opcode_name;
    this->bytecount = bytecount;
}
