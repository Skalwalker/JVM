#include "../include/Instructions.hpp"

Instructions::Instructions() {
    string line;
    ifstream myfile ("external_data/opcode_mnemonics.txt");

    string opcode_name, opcode_numb;
    uint8_t numb;
    while (myfile >> opcode_name >> opcode_numb) {
        numb = stoi(opcode_numb, nullptr, 16);
        opcode[numb] = opcode_name;
    }
}
