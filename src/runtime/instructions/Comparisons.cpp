#include "../../../include/runtime/instructions/Instruction.hpp"

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

uint32_t Instruction::ifle(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t branchbyte1 = bytecode[++frame->local_pc];
    uint8_t branchbyte2 = bytecode[++frame->local_pc];
    int16_t offset = (branchbyte1 << 8) | branchbyte2;
    int value;

    value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    //Passou no teste
    if (value <= 0) {
        frame->local_pc += offset-2;
        return frame->local_pc;
    }
    // Nao passou
    return ++frame->local_pc;
}

uint32_t Instruction::ifge(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t branchbyte1 = bytecode[++frame->local_pc];
    uint8_t branchbyte2 = bytecode[++frame->local_pc];
    int16_t offset = (branchbyte1 << 8) | branchbyte2;
    int value;

    value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    //Passou no teste
    if (value >= 0) {
        frame->local_pc += offset-2;
        return frame->local_pc;
    }
    // Nao passou
    return ++frame->local_pc;
}

uint32_t Instruction::ifeq(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t branchbyte1 = bytecode[++frame->local_pc];
    uint8_t branchbyte2 = bytecode[++frame->local_pc];
    int16_t offset = (branchbyte1 << 8) | branchbyte2;
    int value;

    value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    //Passou no teste
    if (value == 0) {
        frame->local_pc += offset-2;
        return frame->local_pc;
    }
    // Nao passou
    return ++frame->local_pc;
}

uint32_t Instruction::ifne(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t branchbyte1 = bytecode[++frame->local_pc];
    uint8_t branchbyte2 = bytecode[++frame->local_pc];
    int16_t offset = (branchbyte1 << 8) | branchbyte2;
    int value;

    value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    //Passou no teste
    if (value != 0) {
        frame->local_pc += offset-2;
        return frame->local_pc;
    }
    // Nao passou
    return ++frame->local_pc;
}

uint32_t Instruction::iflt(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t branchbyte1 = bytecode[++frame->local_pc];
    uint8_t branchbyte2 = bytecode[++frame->local_pc];
    int16_t offset = (branchbyte1 << 8) | branchbyte2;
    int value;

    value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    //Passou no teste
    if (value < 0) {
        frame->local_pc += offset-2;
        return frame->local_pc;
    }
    // Nao passou
    return ++frame->local_pc;
}

uint32_t Instruction::ifgt(Frame* frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t branchbyte1 = bytecode[++frame->local_pc];
    uint8_t branchbyte2 = bytecode[++frame->local_pc];
    int16_t offset = (branchbyte1 << 8) | branchbyte2;
    int value;

    value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    //Passou no teste
    if (value > 0) {
        frame->local_pc += offset-2;
        return frame->local_pc;
    }
    // Nao passou
    return ++frame->local_pc;
}

uint32_t Instruction::fcmpg(Frame* frame) {
    float value2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    float value1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    Type val;
    val.tag = TAG_INT;
    if (value1 > value2) {
        val.type_int = 1;
        frame->operandStack.push(val);
    } else if (value1 == value2) {
        val.type_int = 0;
        frame->operandStack.push(val);
    } else if (value1 < value2) {
        val.type_int = -1;
        frame->operandStack.push(val);
    } else if (isnan(value1) || isnan(value2)) {
        val.type_int = 1;
        frame->operandStack.push(val);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::fcmpl(Frame* frame) {
    float value2 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    float value1 = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    Type val;
    val.tag = TAG_INT;
    if (value1 > value2) {
        val.type_int = 1;
        frame->operandStack.push(val);
    } else if (value1 == value2) {
        val.type_int = 0;
        frame->operandStack.push(val);
    } else if (value1 < value2) {
        val.type_int = -1;
        frame->operandStack.push(val);
    } else if (isnan(value1) || isnan(value2)) {
        val.type_int = -1;
        frame->operandStack.push(val);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::dcmpg(Frame* frame) {
    double value2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    double value1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    Type val;
    val.tag = TAG_INT;
    if (value1 > value2) {
        val.type_int = 1;
        frame->operandStack.push(val);
    } else if (value1 == value2) {
        val.type_int = 0;
        frame->operandStack.push(val);
    } else if (value1 < value2) {
        val.type_int = -1;
        frame->operandStack.push(val);
    } else if (isnan(value1) || isnan(value2)) {
        val.type_int = 1;
        frame->operandStack.push(val);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::dcmpl(Frame* frame) {
    double value2 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    double value1 = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    Type val;
    val.tag = TAG_INT;
    if (value1 > value2) {
        val.type_int = 1;
        frame->operandStack.push(val);
    } else if (value1 == value2) {
        val.type_int = 0;
        frame->operandStack.push(val);
    } else if (value1 < value2) {
        val.type_int = -1;
        frame->operandStack.push(val);
    } else if (isnan(value1) || isnan(value2)) {
        val.type_int = 1;
        frame->operandStack.push(val);
    }

    return ++frame->local_pc;
}
