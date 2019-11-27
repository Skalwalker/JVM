#include "../../../include/runtime/instructions/Instruction.hpp"

/** \file Instruction.cpp
 *
 *
 */

Instruction::Instruction() { }

Instruction::Instruction(string opcode_name) {
    this->mnemonic = opcode_name;
}

Instruction::Instruction(string opcode_name, uint32_t bytecount) {
    this->classLoader = classLoader;
    this->mnemonic = opcode_name;
    this->bytecount = bytecount;
}

tuple<string, string, string>Instruction::methodInfoSplit(string methodinfo) {
    int j = 0;
    int w = 0;

    while (w < methodinfo.size() && methodinfo[w+1] != '#') {
        w++;
    }
    string className = methodinfo.substr(0,w+1);
    string nameAndType = methodinfo.substr(w+2, methodinfo.size());
    while (j < nameAndType.size() && nameAndType[j+1] != '$') {
        j++;
    }
    string methodName = nameAndType.substr(0,j+1);
    string descriptor = nameAndType.substr(j+2,nameAndType.size());

    return make_tuple(className, methodName, descriptor);
}
