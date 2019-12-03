/** \file Loads.cpp
 * \brief Definições das instruções de load declaradas em Instruction.
 *
 * Referente às instruções definidas em Instruction.hpp do tipo Load da Java SE 8 Edition.
 * Instruções do tipo Load recuperam valores do vetor de variáveis locais e empilham na pilha de operandos.
 *
 * \date Date: 29/11/2019
 */

#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::fload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::fload_0(Frame * frame){
    Type value = frame->localVariables[0];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::fload_1(Frame * frame){
    Type value = frame->localVariables[1];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::fload_2(Frame * frame){
    Type value = frame->localVariables[2];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::fload_3(Frame * frame){
    Type value = frame->localVariables[3];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::iload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type val = frame->localVariables[index];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::iload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);
    return ++frame->local_pc;
}


uint32_t Instruction::iload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::iload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::iload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::lload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::lload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::lload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::lload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::lload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::dload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value = frame->localVariables[index];
    frame->operandStack.push(value);

    return ++frame->local_pc;
}


uint32_t Instruction::dload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::dload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::dload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::dload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::saload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();

    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)arrayref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value;
    value.tag = TAG_INT;
    value.type_int = arr->at(index).type_int;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::aload(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type val = frame->localVariables[index];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

uint32_t Instruction::aload_0(Frame * frame){
    Type val = frame->localVariables[0];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::aload_1(Frame * frame){
    Type val = frame->localVariables[1];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::aload_2(Frame * frame){
    Type val = frame->localVariables[2];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}


uint32_t Instruction::aload_3(Frame * frame){
    Type val = frame->localVariables[3];
    frame->operandStack.push(val);

    return ++frame->local_pc;
}

uint32_t Instruction::iaload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arr_ref = frame->operandStack.top();
    frame->operandStack.pop();

    if (arr_ref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* array = (vector<Type>*)arr_ref.type_reference;

    if(index > array->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value;
    value.tag = TAG_INT;
    value.type_int = array->at(index).type_int;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::faload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();

    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)arrayref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value;
    value.tag = TAG_FLOAT;
    value.type_float = arr->at(index).type_float;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::daload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)arrayref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value;
    value.tag = TAG_DOUBLE;
    value.type_double = arr->at(index).type_double;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::laload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)arrayref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value;
    value.tag = TAG_LONG;
    value.type_long = arr->at(index).type_long;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::baload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)arrayref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value = arr->at(index);

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::caload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)arrayref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    Type value = arr->at(index);

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::aaload(Frame * frame){
    Type array_ref;
    int32_t index;
    index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    array_ref = frame->operandStack.top();
    frame->operandStack.pop();

    if (array_ref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arr = (vector<Type>*)array_ref.type_reference;

    if(index > arr->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    cout << array_ref.type_reference << endl;

    Type res = arr->at(index);

    frame->operandStack.push(res);

    return ++frame->local_pc;
}
