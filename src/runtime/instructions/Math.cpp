/** \file Math.cpp
 * \brief Definições das instruções de Math declaradas em Instruction.
 *
 * Referente às instruções definidas em Instruction.hpp do tipo Math da Java SE 8 Edition.
 * Instruções do tipo Math realizam operações aritméticas de tipos definidos.
 *
 * \date Date: 29/11/2019
 */

#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::iadd(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    // cout << val1 << " " << val2 << endl;
    res.type_int = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::isub(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::imul(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::idiv(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if(val2 == 0) {
        ExceptionThrower::arithmeticException(0);
    } else {
        res.tag = TAG_INT;
        res.type_int = val1 / val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::irem(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if(val2 == 0) {
        ExceptionThrower::arithmeticException(0);
    } else {
        res.tag = TAG_INT;
        res.type_int = val1 % val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::ineg(Frame * frame) {
    int32_t val1;
    Type res;
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ishl(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 << val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ishr(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iushr(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val2 = val2 & 0x0000001F;
    res.tag = TAG_INT;
    res.type_int = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iand(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 & val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ior(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 | val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ixor(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
    res.type_int = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ladd(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lsub(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lmul(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ldiv(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    if(val2 == 0) {
        ExceptionThrower::arithmeticException(0);
    } else {
        res.tag = TAG_LONG;
        res.type_long = val1 / val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::lrem(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();

    if(val2 == 0) {
        ExceptionThrower::arithmeticException(0);
    } else {
        res.tag = TAG_INT;
        res.type_long = val1 % val2;
        frame->operandStack.push(res);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::lneg(Frame * frame) {
    int64_t val1;
    Type res;
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::land(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 & val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lshl(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val2 = val2 & 0x0000003F;
    res.tag = TAG_LONG;
    res.type_long = val1 << val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lshr(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val2 = val2 & 0x0000003F;
    res.tag = TAG_LONG;
    res.type_long = val1 >> val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lor(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 | val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lxor(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    res.tag = TAG_LONG;
    res.type_long = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iinc(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    int8_t imm_const = bytecode[++frame->local_pc];
    int32_t temp, sign_ext;

    sign_ext = imm_const;
    temp = frame->localVariables[index].type_int;
    temp += sign_ext;

    frame->localVariables[index].type_int = temp;

    return ++frame->local_pc;
}

uint32_t Instruction::fadd(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fsub(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fmul(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fdiv(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = val1 / val2;
    cout << val1 / val2 << endl;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::frem(Frame * frame) {
    float val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = fmodf(val1, val2);
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::fneg(Frame * frame) {
    float val1;
    Type res;
    val1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    res.tag = TAG_FLOAT;
    res.type_float = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::dadd(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 + val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::dsub(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 - val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::dmul(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 * val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ddiv(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = val1 / val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::drem(Frame * frame) {
    double val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = fmod(val1,val2);
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::dneg(Frame * frame) {
    double val1;
    Type res;
    val1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    res.tag = TAG_DOUBLE;
    res.type_double = -val1;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}
