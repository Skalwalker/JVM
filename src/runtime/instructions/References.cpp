#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::newarray(Frame *frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t atype = bytecode[++frame->local_pc];
    int count = frame->operandStack.top().type_int;
    frame->operandStack.pop();


    // Type *arr_type = (Type*)malloc(count*(sizeof(Type)));
    // vector<Type>* arr = (vector<Type>*)array_ref.type_reference;
    // vector<Type> arr_type(count);
    vector<Type>* arr_type = new vector<Type>(count);

    Type *value;
    value = (Type*)malloc(sizeof(Type));


    if (atype == T_BOOLEAN) {
        value->tag = TAG_BOOL;
        value->type_boolean = false;
    } else if (atype == T_CHAR) {
        value->tag = TAG_CHAR;
        value->type_char = 0;
    }  else if (atype == T_FLOAT) {
        value->tag = TAG_FLOAT;
        value->type_float = 0.0f;
    }  else if (atype == T_DOUBLE) {
        value->tag = TAG_DOUBLE;
        value->type_double = 0.0;
    }  else if (atype == T_BYTE) {
        value->tag = TAG_BYTE;
        value->type_byte = 0;
    }  else if (atype == T_SHORT) {
        value->tag = TAG_SHORT;
        value->type_short = 0;
    }  else if (atype == T_INT) {
        value->tag = TAG_INT;
        value->type_int = 0;
    }  else if (atype == T_LONG) {
        value->tag = TAG_LONG;
        value->type_long = 0;
    }

    for (int i = 0; i < count; i++) {
        arr_type->at(i) = *value;
    }

    Type arrayReference;
    arrayReference.tag = TAG_REFERENCE;
    arrayReference.type_reference = (uint64_t)&arr_type[0];
    frame->operandStack.push(arrayReference);

    Type res = frame->operandStack.top();
    // Type* arrayPointer = (Type*)(res.type_reference);
    vector<Type>* arrayPointer = (vector<Type>*)res.type_reference;

    return ++frame->local_pc;
}

uint32_t Instruction::getstatic(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string className = frame->constantPool[index-1].getInfo(frame->constantPool);

    if (className.compare("java/lang/System") != 0) {
        cout << "AQUI VAO ACONTECER MUITAS OUTRAS COISAS" << endl;
    }

    return ++frame->local_pc;
}


uint32_t Instruction::invokevirtual(Frame* frame) {
    tuple<string, string, string> methodInfo;
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string method = frame->constantPool[index-1].getInfo(frame->constantPool);
    methodInfo = methodInfoSplit(method);
    string className = get<0>(methodInfo);
    string methodName = get<1>(methodInfo);
    string descriptor = get<2>(methodInfo);

    if (className.compare("java/io/PrintStream") == 0) {
        if (methodName.compare("println") == 0) {
            if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
                string* stringReference = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                cout << *stringReference << endl;
            } else if (descriptor.compare("(I)V") == 0){
                cout << frame->operandStack.top().type_int << endl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(J)V") == 0){
                cout << frame->operandStack.top().type_long << endl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(D)V") == 0){
                cout << frame->operandStack.top().type_double << endl;
                frame->operandStack.pop();
            }  else if (descriptor.compare("(F)V") == 0){
                cout << frame->operandStack.top().type_float << endl;
                frame->operandStack.pop();
            }  else if (descriptor.compare("()V") == 0){
                cout << unsigned(frame->operandStack.top().tag) << endl;
                frame->operandStack.pop();
            }
        }
    }
    return ++frame->local_pc;
}


uint32_t Instruction::invokestatic(Frame* frame){
    tuple<string, string, string> methodInfo;
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string method = frame->constantPool[index-1].getInfo(frame->constantPool);
    methodInfo = methodInfoSplit(method);
    string className = get<0>(methodInfo);
    string methodName = get<1>(methodInfo);
    string descriptor = get<2>(methodInfo);

    ClassFile classfile = classLoader->methodArea->getClassFile(className);
    vector<MethodInfo> methods = classfile.getMethods();
    int i;
    for (i = 0; i < classfile.getMethodsCount(); i++) {
        if(methods[i].name == methodName && methods[i].descriptor == descriptor) {
            break;
        }
    }
    Frame newFrame(frame->constantPool, methods[i], frame->jvmStack);

    // Empilha os argumentos para reverter a ordem
    stack<Type> auxstack;
    i = 1;
    int narg = 0;
    while (descriptor[i] != ')') {
        if (descriptor[i] == '[') {
            while(descriptor[i] == '[') {
                i++;
            }
        } else if (descriptor[i] == 'L') {
            while(descriptor[i] != ';') {
                i++;
            }
        } else if (descriptor[i] != ')') {
            auxstack.push(frame->operandStack.top());
            frame->operandStack.pop();
            narg += 1;
        }
        i++;
    }

    for (i = 0; i < narg; i++) {
        newFrame.localVariables[i] = auxstack.top();
        if (auxstack.top().tag == TAG_LONG || auxstack.top().tag == TAG_DOUBLE) {
            i += 1;
            newFrame.localVariables[i] = auxstack.top();
        }
        auxstack.pop();
    }

    frame->jvmStack->push(newFrame);
    ++frame->local_pc;
    return newFrame.local_pc;
}

// uint32_t Instruction::putstatic(Frame* frame){
// }
//
// uint32_t Instruction::getfield(Frame* frame){
// }
//
// uint32_t Instruction::putfield(Frame* frame){
// }
//
// uint32_t Instruction::getfield(Frame* frame){
// }
//
// uint32_t Instruction::invokespecial(Frame* frame){
// }
//
// uint32_t Instruction::invokeinterface(Frame* frame){
// }
//
// uint32_t Instruction::invokedynamic(Frame* frame){
// }
//
// uint32_t Instruction::new_func(Frame* frame){
//     uint8_t* bytecode = frame->codeAttribute.code;
//     uint8_t byte1 = bytecode[++frame->local_pc];
//     uint8_t byte2 = bytecode[++frame->local_pc];
//
//     uint16_t index = ((uint16_t)byte1 << 8) | byte2;
//
//     Type res;
//     res.tag = TAG_REFERENCE;
//     res.type_reference =  (uint64_t)new string((frame->constantPool[index-1].getInfo(frame->constantPool)));
//
//     frame->operandStack.push(res);
// }

uint32_t Instruction::anewarray(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    int count = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    vector<Type>* arr_type = new vector<Type>(count);

    for(int i = 0; i < count; i++){
        arr_type->at(i).tag = TAG_REFERENCE;
        arr_type->at(i).type_reference = (uint64_t)NULL;
    }

    Type res;
    res.tag = TAG_REFERENCE;
    res.type_reference = (uint64_t)arr_type;

    frame->operandStack.push(res);

    return ++frame->local_pc;

}

uint32_t Instruction::arraylength(Frame* frame){
    Type arrayref = frame->operandStack.top();
    frame->operandStack.pop();

    vector<Type>* type_vec = (vector<Type>*)arrayref.type_reference;
    Type len;
    len.tag = TAG_INT;
    len.type_int = type_vec->size();

    frame->operandStack.push(len);

    return ++frame->local_pc;
}

// uint32_t Instruction::athrow(Frame* frame){
// }
//
// uint32_t Instruction::checkcast(Frame* frame){
// }
//
// uint32_t Instruction::instanceof(Frame* frame){
// }
//
// uint32_t Instruction::monitorenter(Frame* frame){
// }
//
// uint32_t Instruction::monitorexit(Frame* frame){
// }
