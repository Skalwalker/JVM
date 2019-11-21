#include "../../../include/runtime/instructions/Instruction.hpp"

/* MAAAAAAATH */
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
        printf("TODO\n");
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
        printf("TODO\n");
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
    res.tag = TAG_LONG;
    res.type_long = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::lcmp(Frame * frame) {
    int64_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_long;
    frame->operandStack.top();
    res.tag = TAG_INT;
    if (val1 > val2) {
        res.type_int = 1;
    } else if (val1 == val2) {
        res.type_int = 0;
    } else {
        res.type_int = -1;
    }
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::iadd(Frame * frame) {
    int32_t val1, val2;
    Type res;
    val2 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    val1 = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    res.tag = TAG_INT;
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
        printf("TODO\n");
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
        printf("TODO\n");
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
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
    frame->operandStack.top();
    res.tag = TAG_INT;
    res.type_int = val1 ^ val2;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

// uint32_t Instruction::iinc(Frame * frame) {
//     int32_t val1, val2;
//     Type res;
//     val1 = frame->operandStack.top().type_int;
//     frame->operandStack.top();
//     val2 = frame->operandStack.top().type_int;
//     frame->operandStack.pop();
//     res.tag = TAG_INT;
//     res.type_int = val1 + val2;
//     frame->operandStack.push(res);
// }

// uint32_t Instruction::fadd(Frame * frame) {
//
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fsub(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fmul(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fdiv(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::frem(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::fneg(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dadd(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dsub(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dmul(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::ddiv(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::drem(Frame * frame) {
//
//     return ++frame->local_pc;
// }
//
// uint32_t Instruction::dneg(Frame * frame) {
//
//     return ++frame->local_pc;
// }
