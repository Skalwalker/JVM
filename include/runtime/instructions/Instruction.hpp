#ifndef __Instruction_H__
#define __Instruction_H__

#include <cstdint>
#include <string>
#include <math.h>
#include <tuple>
#include "../Frame.hpp"
#include "../../loader/ClassLoader.hpp"
#include "../../models/CPInfo.hpp"

/** \file Instruction.hpp
 * Definição das instruções de acordo com a Java SE 8 Edition.
 * São divididas em 10 tipos:
 * -# Instruções de Load e Store
 *      - iload, iload_<n>, lload, lload_<n>, fload, fload_<n>, dload, dload_<n>, aload, aload_<n> - Loads.cpp
 *      - istore, istore_<n>, lstore, lstore_<n>, fstore, fstore_<n>, dstore, dstore_<n>, astore, astore_<n> - Stores.Cpp
 *      - bipush, sipush, ldc, ldc_w, ldc2_w, aconst_null, iconst_m1, iconst_<i>, lconst_<l>, fconst_<f>, dconst_<d> - Constants.cpp
 *      - wide  ???
 * -# Instruções Aritméticas - Math.cpp
 *      - Add: iadd, ladd, fadd, dadd.
 *      - Subtract: isub, lsub, fsub, dsub.
 *      - Multiply: imul, lmul, fmul, dmul.
 *      - Divide: idiv, ldiv, fdiv, ddiv.
 *      - Remainder: irem, lrem, frem, drem.
 *      - Negate: ineg, lneg, fneg, dneg.
 *      - Shift: ishl, ishr, iushr, lshl, lshr, lushr.
 *      - Bitwise OR: ior, lor.
 *      - Bitwise AND: iand, land.
 *      - Bitwise exclusive OR: ixor, lxor.
 *      - Local variable increment: iinc
 *      - Comparison: dcmpg, dcmpl, fcmpg, fcmpl, lcmp - Comparison.cpp
 * -# Instruções de Conversão de Tipo - Conversions.cpp
 *      - i2l, i2f, i2d, l2f, l2d, e f2d.
 *      - i2l, i2f, i2d, l2f, l2d, e f2d.
 * -# Instruções de Criação e Manipulação de Objetos - Reference.cpp
 *      - new
 *      - newarray, anewarray, multianewarray
 *      - getstatic, putstatic, getfield, putfield
 *      - baload, caload, saload, iaload, laload, faload, daload, aaload
 *      - bastore, castore, sastore, iastore, lastore, fastore, dastore, aastore
 *      - arraylength
 *      - instanceof, checkcast
 * -# Instruções de Gerenciamento da Pilha de Operandos - Stack.cpp
 *      - pop, pop2, dup, dup2, dup_x1, dup2_x1, dup_x2, dup2_x2, swap
 * -# Instruções de Transferência de Controle
 *      - ifeq, ifne, iflt, ifle, ifgt, ifge, ifnull*, ifnonnull*, if_icmpeq, if_icmpne, if_icmplt, if_icmple, if_icmpgt, if_icmpge, if_acmpeq, if_acmpne. - Comparisons.cpp
 *      - tableswitch, lookupswitch - Control.cpp
 *      - goto, goto_w*, jsr, jsr_w, ret - Control.cpp
 * -# Instruções de Invocação de Método e Retorno - References.cpp
 *      - invokevirtual, invokeinterface, invokespecial, invokestatic, invokedynamic
 * -# Instruções de Exceções - ?
 *      - athrow
 * -# Instruções de Sincronização - ?
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

};


#endif
