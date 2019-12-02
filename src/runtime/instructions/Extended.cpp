#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::wide(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t opcode = bytecode[++frame->local_pc];
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = (byte1 << 8) | byte2;
    Type value;

    if (opcode == 0x84) {
        uint8_t constByte1 = bytecode[++frame->local_pc];
        uint8_t constByte2 = bytecode[++frame->local_pc];
        uint16_t imm_const = (constByte1 << 8) | constByte2;

        int32_t temp, sign_ext;

        sign_ext = imm_const;
        temp = frame->localVariables[index].type_int;
        temp += sign_ext;

        frame->localVariables[index].type_int = temp;

    } else {
        //0x15 iload 0x16 lload 0x17 fload 0x18 dload 0x19 aload
        if (opcode == 0x15 || opcode == 0x16 || opcode == 0x17 || opcode == 0x18 || opcode == 0x19) {
            value = frame->localVariables[index];
            frame->operandStack.push(value);

        //0x36 istore 0x37 dstore 0x3a astore
        } else if(opcode == 0x36 || opcode == 0x39) {
            value = frame->operandStack.top();
            frame->operandStack.pop();
            frame->localVariables[index] = value;

        //lstore 0x38 fstore 0x39
        } else if(opcode == 0x37 || opcode == 0x38) {
            value = frame->operandStack.top();
            frame->operandStack.pop();
            frame->localVariables[index] = value;
            frame->localVariables[index+1] = value;
        //0xa9 ret
        } else if(opcode == 0xa9) {
            value = frame->localVariables[index];
            return value.type_returnAddress;
        }
    }

    return ++frame->local_pc;
}


vector<Type>* Instruction::buildArray(vector<int32_t> dim, int index, char type) {
    vector<Type>* arr_type = new vector<Type>(dim[index]);

    if (index == 0) {
        for(int i = 0; i < dim[index];i++) {
            if (type == 'I') {
                arr_type->at(i).tag = TAG_INT;
                arr_type->at(i).type_int = 0;
            } else if (type == 'D') {
                arr_type->at(i).tag = TAG_DOUBLE;
                arr_type->at(i).type_double = 0.0;
            } else if (type == 'F') {
                arr_type->at(i).tag = TAG_FLOAT;
                arr_type->at(i).type_float = 0.0;
            } else if (type == 'C') {
                arr_type->at(i).tag = TAG_CHAR;
                arr_type->at(i).type_char = 0;
            } else if (type == 'S') {
                arr_type->at(i).tag = TAG_INT;
                arr_type->at(i).type_int = 0;
            } else if (type == 'Z') {
                arr_type->at(i).tag = TAG_BOOL;
                arr_type->at(i).type_boolean = false;
            } else if (type == ';') {


            } else if (type == 'B') {
                arr_type->at(i).tag = TAG_INT;
                arr_type->at(i).type_int = 0;
            } else if (type == 'J') {
                arr_type->at(i).tag = TAG_LONG;
                arr_type->at(i).type_long = 0;
            }
        }
        return arr_type;
    }

    for(int i = 0; i < dim[index]; i++){
        arr_type->at(i).tag = TAG_REFERENCE;
        arr_type->at(i).type_reference = (uint64_t)buildArray(dim, index-1, type);
    }

    return arr_type;
}

uint32_t Instruction::multianewarray(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint8_t dimensions = bytecode[++frame->local_pc];

    int16_t index = (byte1 << 8) | byte2;

    vector<int32_t> dim_arr;

    for (int i = 0; i < dimensions; i++){
        int32_t dim = frame->operandStack.top().type_int;
        frame->operandStack.pop();
        if (dim == 0){
            break;
        }
        dim_arr.push_back(dim);
    }

    string cls_name = frame->constantPool[index-1].getInfo(frame->constantPool);
    vector<Type>* arr_type = buildArray(dim_arr, dimensions-1, cls_name[cls_name.size()-1]);

    Type res;
    res.tag = TAG_REFERENCE;
    res.type_reference = (uint64_t)arr_type;
    frame->operandStack.push(res);

    return ++frame->local_pc;
}

uint32_t Instruction::ifnull(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    Type val1;
    val1 = frame->operandStack.top();
    frame->operandStack.pop();

    if (val1.type_reference == (uint64_t)NULL) {
        int16_t offset = (byte1 << 8) | byte2;
        frame->local_pc += offset-2;

        return frame->local_pc;
    }

    return ++frame->local_pc;
}

uint32_t Instruction::ifnonnull(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    Type val1;
    val1 = frame->operandStack.top();
    frame->operandStack.pop();

    if (val1.type_reference != (uint64_t)NULL) {
        int16_t offset = (byte1 << 8) | byte2;
        frame->local_pc += offset-2;

        return frame->local_pc;
    }

    return ++frame->local_pc;
}

uint32_t Instruction::goto_w(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint8_t byte3 = bytecode[++frame->local_pc];
    uint8_t byte4 = bytecode[++frame->local_pc];

    int32_t offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    frame->local_pc += offset-2;

    return frame->local_pc;

}

uint32_t Instruction::jsr_w(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint8_t byte3 = bytecode[++frame->local_pc];
    uint8_t byte4 = bytecode[++frame->local_pc];

    Type res;
    res.tag = TAG_RETURN;
    res.type_returnAddress = ++frame->local_pc;

    frame->operandStack.push(res);

    int32_t offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    frame->local_pc += offset-2;

    return frame->local_pc;
}
