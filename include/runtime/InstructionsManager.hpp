#ifndef __InstructionsManager_H__
#define __InstructionsManager_H__

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include "./instructions/Instruction.hpp"

using namespace std;

class InstructionsManager {
public:
    map<uint8_t, Instruction> opcode;
    InstructionsManager();
    InstructionsManager(ClassLoader*);
    pair<uint8_t, Instruction>* instructionByName(string);
    void setInstructions();
};


#endif
