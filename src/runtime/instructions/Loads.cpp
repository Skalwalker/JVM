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
    vector<Type>* array = (vector<Type>*)frame->operandStack.top().type_reference;

    frame->operandStack.pop();

    Type value;
    value.tag = TAG_INT;
    value.type_int = array->at(index).type_int;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::faload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    vector<Type>* array = (vector<Type>*)frame->operandStack.top().type_reference;

    frame->operandStack.pop();

    Type value;
    value.tag = TAG_FLOAT;
    value.type_float = array->at(index).type_float;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::daload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    vector<Type>* array = (vector<Type>*)frame->operandStack.top().type_reference;

    frame->operandStack.pop();

    Type value;
    value.tag = TAG_DOUBLE;
    value.type_double = array->at(index).type_double;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::laload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    vector<Type>* array = (vector<Type>*)frame->operandStack.top().type_reference;

    frame->operandStack.pop();

    Type value;
    value.tag = TAG_LONG;
    value.type_long = array->at(index).type_long;

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::baload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    vector<Type>* array = (vector<Type>*)frame->operandStack.top().type_reference;

    frame->operandStack.pop();

    Type value = array->at(index);

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::caload(Frame * frame){
    int32_t index = frame->operandStack.top().type_int;
    frame->operandStack.pop();
    vector<Type>* array = (vector<Type>*)frame->operandStack.top().type_reference;

    frame->operandStack.pop();

    Type value = array->at(index);

    frame->operandStack.push(value);

    return ++frame->local_pc;
}

uint32_t Instruction::aaload(Frame * frame){
    Type index, array_ref;
    index = frame->operandStack.top();
    frame->operandStack.pop();
    array_ref = frame->operandStack.top();
    frame->operandStack.pop();


    vector<Type>* arr = (vector<Type>*)array_ref.type_reference;
    Type res = arr->at(index.type_int);

    frame->operandStack.push(res);

    return ++frame->local_pc;
}
