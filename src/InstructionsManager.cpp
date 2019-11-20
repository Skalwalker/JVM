#include "../include/InstructionsManager.hpp"

InstructionsManager::InstructionsManager() {
    string line;
    ifstream myfile ("external_data/opcode_mnemonics.txt");

    string opcode_name, opcode_numb;
    uint32_t bytecount;
    uint8_t numb;
    while (myfile >> opcode_name >> opcode_numb >> bytecount) {
        numb = stoi(opcode_numb, nullptr, 16);
        opcode[numb] = Instruction(opcode_name, bytecount);
    }

    this->instructionByName("getstatic")->second.exec = Instruction::getstatic;
    this->instructionByName("ldc")->second.exec = Instruction::ldc;
    this->instructionByName("invokevirtual")->second.exec = Instruction::invokevirtual;
    this->instructionByName("return")->second.exec = Instruction::returnfunc;
}

pair<uint8_t, Instruction>* InstructionsManager::instructionByName(string name) {
    map<uint8_t, Instruction>::iterator it;
    for(it = opcode.begin(); it != opcode.end(); it++) {
        if (it->second.mnemonic.compare(name) == 0) {
            return reinterpret_cast<pair<uint8_t, Instruction>*>(&(*it));
        }
    }
    return nullptr;
}
