#ifndef __Instruction_H__
#define __Instruction_H__

#include <cstdint>
#include <string>
#include "../Frame.hpp"
#include "../../models/CPInfo.hpp"

#define CONSTANT_STRING 8
#define CONSTANT_INTEGER 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6

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
    static uint32_t ldc2_w(Frame*);
    static uint32_t invokevirtual(Frame*);
    static uint32_t returnfunc(Frame*);
    static uint32_t ladd(Frame*);
    static uint32_t lsub(Frame*);
    static uint32_t lmul(Frame*);
    static uint32_t ldiv(Frame*);
    static uint32_t lneg(Frame*);
    static uint32_t lrem(Frame*);
    static uint32_t lshl(Frame*);
    static uint32_t lshr(Frame*);
    static uint32_t land(Frame*);
    static uint32_t lor(Frame*);
    static uint32_t lxor(Frame*);
    static uint32_t iadd(Frame*);
    static uint32_t isub(Frame *);
    static uint32_t imul(Frame *);
    static uint32_t idiv(Frame *);
    static uint32_t irem(Frame *);
    static uint32_t ineg(Frame *);
    static uint32_t ishl(Frame*);
    static uint32_t ishr(Frame*);
    static uint32_t iushr(Frame*);
    static uint32_t iand(Frame*);
    static uint32_t ior(Frame*);
    static uint32_t ixor(Frame*);
    static uint32_t bipush(Frame*);
    static uint32_t lstore(Frame *);
    static uint32_t lstore_0(Frame *);
    static uint32_t lstore_1(Frame *);
    static uint32_t lstore_2(Frame *);
    static uint32_t lstore_3(Frame *);
    static uint32_t istore_0(Frame *);
    static uint32_t istore_1(Frame *);
    static uint32_t istore_2(Frame *);
    static uint32_t istore_3(Frame *);
    static uint32_t lload(Frame *);
    static uint32_t lload_0(Frame *);
    static uint32_t lload_1(Frame *);
    static uint32_t lload_2(Frame *);
    static uint32_t lload_3(Frame *);
    static uint32_t iload_0(Frame *);
    static uint32_t iload_1(Frame *);
    static uint32_t iload_2(Frame *);
    static uint32_t iload_3(Frame *);
    static uint32_t iconst_m1(Frame *);
    static uint32_t iconst_0(Frame *);
    static uint32_t iconst_1(Frame *);
    static uint32_t iconst_2(Frame *);
    static uint32_t iconst_3(Frame *);
    static uint32_t iconst_4(Frame *);
    static uint32_t iconst_5(Frame *);
    static uint32_t lconst_0(Frame *);
    static uint32_t lconst_1(Frame *);

    static uint32_t lcmp(Frame*);
    static uint32_t ifle(Frame*);
    static uint32_t ifge(Frame*);
    static uint32_t ifeq(Frame*);
};

#endif
