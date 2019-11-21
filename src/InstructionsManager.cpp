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
    this->instructionByName("iadd")->second.exec = Instruction::iadd;
    this->instructionByName("isub")->second.exec = Instruction::isub;
    this->instructionByName("imul")->second.exec = Instruction::imul;
    this->instructionByName("idiv")->second.exec = Instruction::idiv;
    this->instructionByName("irem")->second.exec = Instruction::irem;
    this->instructionByName("ineg")->second.exec = Instruction::ineg;
    this->instructionByName("ishl")->second.exec = Instruction::ishl;
    this->instructionByName("ishr")->second.exec = Instruction::ishr;
    this->instructionByName("iushr")->second.exec = Instruction::iushr;
    this->instructionByName("iand")->second.exec = Instruction::iand;
    this->instructionByName("ior")->second.exec = Instruction::ior;
    this->instructionByName("ixor")->second.exec = Instruction::ixor;
    this->instructionByName("bipush")->second.exec = Instruction::bipush;
    this->instructionByName("istore_0")->second.exec = Instruction::istore_0;
    this->instructionByName("istore_1")->second.exec = Instruction::istore_1;
    this->instructionByName("istore_2")->second.exec = Instruction::istore_2;
    this->instructionByName("istore_3")->second.exec = Instruction::istore_3;
    this->instructionByName("iload_0")->second.exec = Instruction::iload_0;
    this->instructionByName("iload_1")->second.exec = Instruction::iload_1;
    this->instructionByName("iload_2")->second.exec = Instruction::iload_2;
    this->instructionByName("iload_3")->second.exec = Instruction::iload_3;

    this->instructionByName("iconst_m1")->second.exec = Instruction::iconst_m1;
    this->instructionByName("iconst_0")->second.exec = Instruction::iconst_0;
    this->instructionByName("iconst_1")->second.exec = Instruction::iconst_1;
    this->instructionByName("iconst_2")->second.exec = Instruction::iconst_2;
    this->instructionByName("iconst_3")->second.exec = Instruction::iconst_3;
    this->instructionByName("iconst_4")->second.exec = Instruction::iconst_4;
    this->instructionByName("iconst_5")->second.exec = Instruction::iconst_5;

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
