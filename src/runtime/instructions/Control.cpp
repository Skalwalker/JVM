/** \file Control.cpp
 * \brief Definições das instruções de control declaradas em Instruction.
 *
 * Referente às instruções definidas em Instruction.hpp do tipo Control da Java SE 8 Edition.
 * Instruções do tipo Control redirecionam a execução para uma instrução que não é a seguinte à instrução
 * de controle.
 *
 * \date Date: 29/11/2019
 */

#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::returnfunc(Frame * frame) {
    return frame->local_pc;
}

uint32_t Instruction::goto_func(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    int16_t offset;

    offset = (byte1 << 8) | byte2;

    frame->local_pc += offset-2;

    return frame->local_pc;
}

uint32_t Instruction::jsr(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    Type res;
    res.tag = TAG_RETURN;
    res.type_returnAddress = frame->local_pc;
    frame->operandStack.push(res);

    int16_t offset = (byte1 << 8) | byte2;
    frame->local_pc += offset-2;

    return frame->local_pc;
}

uint32_t Instruction::ret(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type res = frame->localVariables[index];

    return res.type_returnAddress;

}

uint32_t Instruction::tableswitch(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint32_t opcode = frame->local_pc;

    Type res = frame->operandStack.top();
    frame->operandStack.pop();

    while ((++frame->local_pc)%4 != 0);
    frame->local_pc--;

    uint8_t defaultByte1 = bytecode[++frame->local_pc];
    uint8_t defaultByte2 = bytecode[++frame->local_pc];
    uint8_t defaultByte3 = bytecode[++frame->local_pc];
    uint8_t defaultByte4 = bytecode[++frame->local_pc];
    int32_t defaultByte = (defaultByte1 << 24) | (defaultByte2 << 16) | (defaultByte3 << 8) | defaultByte4;

    uint8_t lowByte1 = bytecode[++frame->local_pc];
    uint8_t lowByte2 = bytecode[++frame->local_pc];
    uint8_t lowByte3 = bytecode[++frame->local_pc];
    uint8_t lowByte4 = bytecode[++frame->local_pc];
    int32_t low = (lowByte1 << 24) | (lowByte2 << 16) | (lowByte3 << 8) | lowByte4;

    uint8_t highByte1 = bytecode[++frame->local_pc];
    uint8_t highByte2 = bytecode[++frame->local_pc];
    uint8_t highByte3 = bytecode[++frame->local_pc];
    uint8_t highByte4 = bytecode[++frame->local_pc];
    int32_t high = (highByte1 << 24) | (highByte2 << 16) | (highByte3 << 8) | highByte4;

    for (int i = low; i <= high; i++) {
        uint8_t offsetByte1 = bytecode[++frame->local_pc];
        uint8_t offsetByte2 = bytecode[++frame->local_pc];
        uint8_t offsetByte3 = bytecode[++frame->local_pc];
        uint8_t offsetByte4 = bytecode[++frame->local_pc];
        int32_t offset = (highByte1 << 24) | (highByte2 << 16) | (highByte3 << 8) | highByte4;

        if(res.type_int == i) {
            frame->local_pc = opcode + offset;
            return frame->local_pc;
        }
    }

    frame->local_pc = opcode + defaultByte;
    return frame->local_pc;

}

uint32_t Instruction::lookupswitch(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint32_t opcode = frame->local_pc;

    Type res = frame->operandStack.top();
    frame->operandStack.pop();

    while ((++frame->local_pc)%4 != 0);
    frame->local_pc--;

    uint8_t defaultByte1 = bytecode[++frame->local_pc];
    uint8_t defaultByte2 = bytecode[++frame->local_pc];
    uint8_t defaultByte3 = bytecode[++frame->local_pc];
    uint8_t defaultByte4 = bytecode[++frame->local_pc];
    int32_t defaultByte = (defaultByte1 << 24) | (defaultByte2 << 16) | (defaultByte3 << 8) | defaultByte4;

    uint8_t npairs1 = bytecode[++frame->local_pc];
    uint8_t npairs2 = bytecode[++frame->local_pc];
    uint8_t npairs3 = bytecode[++frame->local_pc];
    uint8_t npairs4 = bytecode[++frame->local_pc];
    int32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;


    for (int i = 0; i <= npairs; i++) {
        uint8_t matchByte1 = bytecode[++frame->local_pc];
        uint8_t matchByte2 = bytecode[++frame->local_pc];
        uint8_t matchByte3 = bytecode[++frame->local_pc];
        uint8_t matchByte4 = bytecode[++frame->local_pc];
        int32_t match = (matchByte1 << 24) | (matchByte2 << 16) | (matchByte3 << 8) | matchByte4;

        uint8_t offsetByte1 = bytecode[++frame->local_pc];
        uint8_t offsetByte2 = bytecode[++frame->local_pc];
        uint8_t offsetByte3 = bytecode[++frame->local_pc];
        uint8_t offsetByte4 = bytecode[++frame->local_pc];
        int32_t offset = (offsetByte1 << 24) | (offsetByte2 << 16) | (offsetByte3 << 8) | offsetByte4;

        if(res.type_int == match) {
            frame->local_pc = opcode + offset;
            return frame->local_pc;
        }
    }

    frame->local_pc = opcode + defaultByte;
    return frame->local_pc;
}
//
uint32_t Instruction::ireturn(Frame * frame){
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* caller = &(frame->jvmStack->top());
    caller->operandStack.push(value);
    return caller->local_pc;
}

uint32_t Instruction::dreturn(Frame * frame){
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* caller = &(frame->jvmStack->top());
    caller->operandStack.push(value);
    return caller->local_pc;
}

uint32_t Instruction::lreturn(Frame * frame){
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* caller = &(frame->jvmStack->top());
    caller->operandStack.push(value);
    return caller->local_pc;
}

uint32_t Instruction::freturn(Frame * frame){
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* caller = &(frame->jvmStack->top());
    caller->operandStack.push(value);
    return caller->local_pc;
}

uint32_t Instruction::areturn(Frame * frame){
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->jvmStack->pop();

    Frame* caller = &(frame->jvmStack->top());
    caller->operandStack.push(value);
    return caller->local_pc;
}
