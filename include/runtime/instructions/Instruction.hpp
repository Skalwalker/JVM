#ifndef __Instruction_H__
#define __Instruction_H__

#include <cstdint>
#include <string>
#include <math.h>
#include <tuple>
#include "../../execution/ExceptionThrower.hpp"
#include "../Frame.hpp"
#include "../../loader/ClassLoader.hpp"
#include "../../models/CPInfo.hpp"

/** \file Instruction.hpp
 * Definição das instruções de acordo com a Java SE 8 Edition.
 * São divididas nos tipos:
 * -# Conversions: \n
 * nop, aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0,
 * lconst_1, fconst_0, fconst_1, fconst_2, dconst_0, dconst_1, bipush, sipush, ldc, ldc_w, ldc2_w
 * -# Loads: \n
 * iload, lload, fload, dload, aload, iload_0, iload_1, iload_2, iload_3, lload_0, lload_1, lload_2,
 * lload_3, fload_0, fload_1, fload_2, fload_3, dload_0, dload_1, dload_2, dload_3, aload_0, aload_1,
 * aload_2, aload_3, iaload, laload, faload, daload, aaload, baload, caload, saload
 * -# Stores: \n
 * istore, lstore, fstore, dstore, astore, istore_0, istore_1, istore_2, istore_3, lstore_0, lstore_1,
 * lstore_2, lstore_3, fstore_0, fstore_1, fstore_2, fstore_3, dstore_0, dstore_1, dstore_2, dstore_3, astore_0,
 * astore_1, astore_2, astore_3, iastore, lastore, fastore, dastore, aastore, bastore, castore, sastore
 * -# Stack: \n
 * pop, pop2, dup, dup_x1, dup_x2, dup2, dup2_x1, dup2_x2, swap
 * -# Math: \n
 * iadd, ladd, fadd, dadd, isub, lsub, fsub, dsub, imul, lmul, fmul, dmul, idiv, ldiv, fdiv, ddiv, irem, lrem,
 * frem, drem, ineg, lneg, fneg, dneg, ishl, lshl, ishr, lshr, iushr, lushr, iand, land, ior, lor, ixor, lxor, iinc
 * -# Conversions: \n
 * i2l, i2f, i2d, l2i, l2f, l2d, f2i, f2l, f2d, d2i, d2l, d2f, i2b, i2c, i2s
 * -# Comparisons: \n
 * lcmp, fcmpl, fcmpg, dcmpl, dcmpg, ifeq, ifne, iflt, ifge, ifgt, ifle, if_icmpeq, if_icmpne, if_icmplt, if_icmpge,
 * if_icmpgt, if_icmple, if_acmpeq, if_acmpne
 * -# References: \n
 * getstatic, putstatic, getfield, putfield, invokevirtual, invokespecial, invokestatic, invokeinterface, invokedynamic,
 * new, newarray, anewarray, arraylength, athrow, checkcast, instanceof, monitorenter, monitorexit
 * -# Control: \n
 * goto, jsr, ret, tableswitch, lookupswitch, ireturn, lreturn, freturn, dreturn, areturn, return
 * -# Extended: \n
 * wide, multianewarray, ifnull, ifnonnull, goto_w, jsr_w
 * -# Reserved: \n
 * breakpoint, impdep1, impdep2
 */

#define CONSTANT_STRING 8
#define CONSTANT_INTEGER 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6

#define T_BOOLEAN 4
#define T_CHAR 5
#define T_FLOAT 6
#define T_DOUBLE 7
#define T_BYTE 8
#define T_SHORT 9
#define T_INT 10
#define T_LONG 11

using namespace std;

class Instruction {
public:
    string mnemonic;
    uint32_t bytecount;
    static ClassLoader * classLoader;
    uint32_t (*exec)(Frame*);
    Instruction(string);
    Instruction(string, uint32_t);
    Instruction();
    static tuple<string, string, string> methodInfoSplit(string);

    static uint32_t getstatic(Frame*);
    static uint32_t ldc(Frame*);
    static uint32_t ldc2_w(Frame*);
    static uint32_t invokevirtual(Frame*);
    static uint32_t invokestatic(Frame*);
    static uint32_t returnfunc(Frame*);
    static uint32_t ireturn(Frame*);
    static uint32_t lreturn(Frame*);
    static uint32_t dreturn(Frame*);
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
    static uint32_t iinc(Frame*);
    static uint32_t fadd(Frame *);
    static uint32_t fsub(Frame *);
    static uint32_t fmul(Frame *);
    static uint32_t fdiv(Frame *);
    static uint32_t frem(Frame *);
    static uint32_t fneg(Frame *);
    static uint32_t bipush(Frame*);
    static uint32_t sipush(Frame*);

    static uint32_t dadd(Frame *);
    static uint32_t dsub(Frame *);
    static uint32_t dmul(Frame *);
    static uint32_t ddiv(Frame *);
    static uint32_t drem(Frame *);
    static uint32_t dneg(Frame *);

    static uint32_t fstore(Frame *);
    static uint32_t fstore_0(Frame *);
    static uint32_t fstore_1(Frame *);
    static uint32_t fstore_2(Frame *);
    static uint32_t fstore_3(Frame *);

    static uint32_t lstore(Frame *);
    static uint32_t lstore_0(Frame *);
    static uint32_t lstore_1(Frame *);
    static uint32_t lstore_2(Frame *);
    static uint32_t lstore_3(Frame *);

    static uint32_t istore(Frame *);
    static uint32_t istore_0(Frame *);
    static uint32_t istore_1(Frame *);
    static uint32_t istore_2(Frame *);
    static uint32_t istore_3(Frame *);

    static uint32_t dstore(Frame *);
    static uint32_t dstore_0(Frame *);
    static uint32_t dstore_1(Frame *);
    static uint32_t dstore_2(Frame *);
    static uint32_t dstore_3(Frame *);

    static uint32_t iastore(Frame *);
    static uint32_t dastore(Frame *);
    static uint32_t fastore(Frame *);
    static uint32_t castore(Frame *);
    static uint32_t sastore(Frame *);
    static uint32_t lastore(Frame *);
    static uint32_t bastore(Frame *);
    static uint32_t astore(Frame *);
    static uint32_t astore_0(Frame *);
    static uint32_t astore_1(Frame *);
    static uint32_t astore_2(Frame *);
    static uint32_t astore_3(Frame *);

    static uint32_t lload(Frame *);
    static uint32_t lload_0(Frame *);
    static uint32_t lload_1(Frame *);
    static uint32_t lload_2(Frame *);
    static uint32_t lload_3(Frame *);

    static uint32_t aload_0(Frame *);
    static uint32_t aload_1(Frame *);
    static uint32_t aload_2(Frame *);
    static uint32_t aload_3(Frame *);
    static uint32_t iaload(Frame *);
    static uint32_t faload(Frame *);
    static uint32_t laload(Frame *);
    static uint32_t daload(Frame *);
    static uint32_t baload(Frame *);
    static uint32_t caload(Frame *);


    static uint32_t fload(Frame *);
    static uint32_t fload_0(Frame *);
    static uint32_t fload_1(Frame *);
    static uint32_t fload_2(Frame *);
    static uint32_t fload_3(Frame *);

    static uint32_t iload(Frame *);
    static uint32_t iload_0(Frame *);
    static uint32_t iload_1(Frame *);
    static uint32_t iload_2(Frame *);
    static uint32_t iload_3(Frame *);

    static uint32_t dload(Frame *);
    static uint32_t dload_0(Frame *);
    static uint32_t dload_1(Frame *);
    static uint32_t dload_2(Frame *);
    static uint32_t dload_3(Frame *);

    static uint32_t iconst_m1(Frame *);
    static uint32_t iconst_0(Frame *);
    static uint32_t iconst_1(Frame *);
    static uint32_t iconst_2(Frame *);
    static uint32_t iconst_3(Frame *);
    static uint32_t iconst_4(Frame *);
    static uint32_t iconst_5(Frame *);
    static uint32_t lconst_0(Frame *);
    static uint32_t lconst_1(Frame *);
    static uint32_t dconst_0(Frame *);
    static uint32_t dconst_1(Frame *);
    static uint32_t fconst_0(Frame *);
    static uint32_t fconst_1(Frame *);
    static uint32_t fconst_2(Frame *);

    static uint32_t lcmp(Frame*);
    static uint32_t ifle(Frame*);
    static uint32_t ifge(Frame*);
    static uint32_t ifeq(Frame*);
    static uint32_t ifne(Frame*);
    static uint32_t iflt(Frame*);
    static uint32_t ifgt(Frame*);
    static uint32_t fcmpl(Frame*);
    static uint32_t fcmpg(Frame*);
    static uint32_t dcmpl(Frame*);
    static uint32_t dcmpg(Frame*);
    static uint32_t if_icmpeq(Frame*);
    static uint32_t if_icmpne(Frame*);
    static uint32_t if_icmplt(Frame*);
    static uint32_t if_icmpge(Frame*);
    static uint32_t if_icmpgt(Frame*);
    static uint32_t if_icmple(Frame*);
    static uint32_t if_acmpeq(Frame*);
    static uint32_t if_acmpne(Frame*);
    static uint32_t goto_func(Frame *);

    static uint32_t f2d(Frame *);
    static uint32_t f2i(Frame *);
    static uint32_t f2l(Frame *);
    static uint32_t d2f(Frame *);
    static uint32_t d2i(Frame *);
    static uint32_t d2l(Frame *);
    static uint32_t l2f(Frame *);
    static uint32_t l2i(Frame *);
    static uint32_t l2d(Frame *);
    static uint32_t i2d(Frame*);
    static uint32_t i2l(Frame*);
    static uint32_t i2f(Frame*);
    static uint32_t i2b(Frame*);
    static uint32_t i2s(Frame*);
    static uint32_t i2c(Frame*);

    static uint32_t jsr(Frame *);
    static uint32_t ret(Frame *);

    static uint32_t newarray(Frame *);

    static uint32_t pop(Frame *);
    static uint32_t pop2(Frame *);
    static uint32_t dup(Frame *);
    static uint32_t dup2(Frame *);
    static uint32_t dup_x1(Frame *);
    static uint32_t dup_x2(Frame *);
    static uint32_t dup2_x1(Frame *);
    static uint32_t dup2_x2(Frame *);
    static uint32_t swap(Frame *);

    // static uint32_t new_func(Frame*);

    static uint32_t ifnonnull(Frame*);
    static uint32_t ifnull(Frame*);
    static uint32_t goto_w(Frame*);
    static uint32_t jsr_w(Frame*);
    static uint32_t nop(Frame*);
    static uint32_t tableswitch(Frame*);
    static uint32_t lookupswitch(Frame*);
    static uint32_t aconst_null(Frame*);
    static uint32_t anewarray(Frame*);
    static uint32_t arraylength(Frame*);
    static uint32_t aaload(Frame *);
    static uint32_t aastore(Frame *);
    static uint32_t multianewarray(Frame*);
    static uint32_t areturn(Frame *);
    static uint32_t freturn(Frame *);
    static uint32_t aload(Frame *);
    static vector<Type>* buildArray(vector<int32_t> dim, int index, char type);
    static uint32_t wide(Frame*);
    static uint32_t saload(Frame *);

};


#endif
