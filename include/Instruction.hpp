#ifndef __Instruction_H__
#define __Instruction_H__

#include <cstdint>
#include <string>
#include "Frame.hpp"
#include "CPInfo.hpp"

using namespace std;

class Instruction {
public:
    string mnemonic;
    uint32_t bytecount;
    uint32_t (*exec)(Frame*);
    Instruction(string);
    Instruction(string, uint32_t);
    Instruction();

    static uint32_t getstatic(Frame*);
    static uint32_t ldc(Frame*);
    static uint32_t invokevirtual(Frame*);
    static uint32_t returnfunc(Frame*);
};

#endif
