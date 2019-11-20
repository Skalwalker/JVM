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
    static uint32_t iadd(Frame*);
    static uint32_t isub(Frame *);
    static uint32_t imul(Frame *);
    static uint32_t ineg(Frame *);
    static uint32_t ishl(Frame*);
    static uint32_t ishr(Frame*);
    static uint32_t iushr(Frame*);
    static uint32_t iand(Frame*);
    static uint32_t ior(Frame*);
    static uint32_t ixor(Frame*);
    static uint32_t bipush(Frame*);
    static uint32_t istore_0(Frame *);
    static uint32_t istore_1(Frame *);
    static uint32_t istore_2(Frame *);
    static uint32_t istore_3(Frame *);
    static uint32_t iload_0(Frame *);
    static uint32_t iload_1(Frame *);
    static uint32_t iload_2(Frame *);
    static uint32_t iload_3(Frame *);
};

#endif
