#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::fstore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_0(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_1(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_2(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fstore_3(Frame * frame){
    Type value;
    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::istore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];

    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;


    return ++frame->local_pc;
}

uint32_t Instruction::istore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::istore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}


uint32_t Instruction::lstore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type value;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = value;
    frame->localVariables[index+1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::lstore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;
    frame->localVariables[4] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore(Frame * frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type value;

    value = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[index] = value;
    frame->localVariables[index+1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_0(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[0] = val;
    frame->localVariables[1] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_1(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[1] = val;
    frame->localVariables[2] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_2(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[2] = val;
    frame->localVariables[3] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::dstore_3(Frame * frame){
    Type val;
    val = frame->operandStack.top();
    frame->operandStack.pop();
    frame->localVariables[3] = val;
    frame->localVariables[4] = val;

    return ++frame->local_pc;
}

uint32_t Instruction::iastore(Frame * frame) {
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    Type arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    vector<Type>* arrayPointer = (vector<Type>*)arrayref.type_reference;

    if(index > arrayPointer->size() || index < 0) {
        ExceptionThrower::arrayIndexOutOfBounds(index);
    }

    arrayPointer->at(index) = value;

    return ++frame->local_pc;
}

uint32_t Instruction::lastore(Frame * frame) {
    uint64_t value = frame->operandStack.top().type_long;
    frame->operandStack.pop();
    int index = frame->operandStack.top().type_int;
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

    arr->at(index).type_long = value;

    return ++frame->local_pc;
}

uint32_t Instruction::dastore(Frame * frame) {
    double value = frame->operandStack.top().type_double;
    frame->operandStack.pop();
    int index = frame->operandStack.top().type_int;
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

    arr->at(index).type_double = value;

    return ++frame->local_pc;
}

uint32_t Instruction::fastore(Frame * frame) {
    float value = frame->operandStack.top().type_float;
    frame->operandStack.pop();
    int index = frame->operandStack.top().type_int;
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

    arr->at(index).type_float = value;

    return ++frame->local_pc;
}

uint32_t Instruction::sastore(Frame * frame) {
    int16_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    int index = frame->operandStack.top().type_int;
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
    arr->at(index).type_int = value;

    return ++frame->local_pc;
}

uint32_t Instruction::bastore(Frame * frame) {
    int32_t value = frame->operandStack.top().type_int;
    frame->operandStack.pop();
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

    arr->at(index).type_int = (int32_t)((int8_t)value);

    return ++frame->local_pc;
}

uint32_t Instruction::castore(Frame * frame) {
    uint8_t value = frame->operandStack.top().type_char;
    frame->operandStack.pop();
    int index = frame->operandStack.top().type_int;
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

    arr->at(index).type_char = value;

    return ++frame->local_pc;
}

uint32_t Instruction::astore(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t index = bytecode[++frame->local_pc];
    Type value = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localVariables[index] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::astore_0(Frame * frame) {
    Type value = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localVariables[0] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::astore_1(Frame * frame) {
    Type value = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localVariables[1] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::astore_2(Frame * frame) {
    Type value = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localVariables[2] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::astore_3(Frame * frame) {
    Type value = frame->operandStack.top();
    frame->operandStack.pop();

    frame->localVariables[3] = value;

    return ++frame->local_pc;
}

uint32_t Instruction::aastore(Frame * frame) {
    Type value = frame->operandStack.top();
    frame->operandStack.pop();
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
    arr->at(index) = value;

    return ++frame->local_pc;
}
