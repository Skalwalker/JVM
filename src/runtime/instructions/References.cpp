#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::newarray(Frame *frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t atype = bytecode[++frame->local_pc];
    int count = frame->operandStack.top().type_int;
    frame->operandStack.pop();


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
        return ++frame->local_pc;
    }

    classLoader->loadClassFile(className);
    ClassFile classFile = classLoader->methodArea->getClassFile(className);
    vector<CPInfo> constantPool = classFile.getConstantPool();
    vector<FieldInfo> fields = classFile.getFields();
    FieldInfo field;
    bool foundField = false;
    string descriptor;

    for (int i = 0; i < classFile.getFieldsCount() && !foundField; i++) {
        field = fields[i];
        uint16_t nameIndex = field.name_index;
        uint16_t descriptorIndex = field.descriptor_index;
        string name = constantPool[nameIndex-1].getInfo(constantPool);
        descriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
        if (name.compare(name) == 0 && descriptor.compare(descriptor) == 0) {
            foundField = true;
        }
    }

    if (!foundField) {
        printf("getstatic: o field especificado nao pode ser resolvido! Deve estar em uma superclasse ou superinterface! Falta implementar!\n");
        exit(0);
    }

    if (descriptor.compare("C") == 0) {
        frame->operandStack.push(field.static_value);
    }
    else if (descriptor.compare("I") == 0) {
        frame->operandStack.push(field.static_value);
    }
    else if (descriptor.compare("F") == 0) {
        frame->operandStack.push(field.static_value);
    }
    else if (descriptor.compare("D") == 0) {
        frame->operandStack.push(field.static_value);
    }
    else if (descriptor.compare("J") == 0) {
        frame->operandStack.push(field.static_value);
    }
    else if (descriptor.compare("Z") == 0) {
        frame->operandStack.push(field.static_value);
    }
    else if (descriptor[0] == '[') {
        frame->operandStack.push(field.static_value);
    }
    else {
        printf("getstatic: tipo do descritor nao reconhecido: %s\n", descriptor.c_str());
        exit(0);
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
        if (methodName.compare("println") == 0 || methodName.compare("print") == 0) {
            string isendl;
            if (methodName.compare("println") == 0) {
                isendl = "\n";
            } else if (methodName.compare("print") == 0) {
                isendl = "";
            }
            if (descriptor.compare("(Ljava/lang/String;)V") == 0) {
                string* stringReference = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                cout << *stringReference << isendl;
            } else if (descriptor.compare("(I)V") == 0){
                if (frame->operandStack.top().tag == TAG_INT) {
                    cout << frame->operandStack.top().type_int << isendl;

                } else if (frame->operandStack.top().tag == TAG_SHORT) {
                    cout << frame->operandStack.top().type_short << isendl;

                }  else if (frame->operandStack.top().tag == TAG_BYTE) {
                    cout << frame->operandStack.top().type_byte << isendl;
                }
                frame->operandStack.pop();
            } else if (descriptor.compare("(J)V") == 0){
                cout << frame->operandStack.top().type_long << isendl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(D)V") == 0){
                cout << frame->operandStack.top().type_double << isendl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(C)V") == 0){
                cout << frame->operandStack.top().type_char << isendl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(F)V") == 0){
                cout << frame->operandStack.top().type_float << isendl;
                frame->operandStack.pop();
            } else if (descriptor.compare("()V") == 0){
                cout << unsigned(frame->operandStack.top().tag) << isendl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(Z)V") == 0){
                cout << frame->operandStack.top().type_boolean << isendl;
                frame->operandStack.pop();
            }
        }
    } else {
        stack<Type> auxstack;
        for (int i = 1; descriptor[i] != ')'; i++) {
            if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            }
            else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            }
            else if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
            else if (descriptor[i] == '[') {
                while (descriptor[i] == '[') {
                    i++;
                }
                if (descriptor[i] == 'L') {
                    while (descriptor[i] != ';') {
                        i++;
                    }
                }
            }
            else {
                cout << "Tipo de descritor nao reconhecido na contagem: " << descriptor[i] << endl;
                exit(0);
            }
            auxstack.push(frame->operandStack.top());
            frame->operandStack.pop();
        }

        bool foundMethod = false;
        vector<CPInfo> constantPool;

        Type objectref = frame->operandStack.top();
        frame->operandStack.pop();
        map<string, Type>* object = (map<string, Type>*)objectref.type_reference;
        string * objectClassName = (string*)object->at("<this_class>").type_reference;

        classLoader->loadClassFile(*objectClassName);
        MethodArea* methodArea = classLoader->methodArea;
        ClassFile objectClassFile = methodArea->getClassFile(*objectClassName);

        constantPool = objectClassFile.getConstantPool();
        vector<MethodInfo> methods = objectClassFile.getMethods();

        MethodInfo method;
        for (int i = 0; i < objectClassFile.getMethodsCount() && !foundMethod; i++) {
            method = methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = constantPool[nameIndex-1].getInfo(constantPool);
            string methodDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
            if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                foundMethod = true;
            }
        }

        if (!foundMethod) {
            do {
                classLoader->loadClassFile(*objectClassName);
                MethodArea * methodArea = classLoader->methodArea;
                ClassFile objectClassFile = methodArea->getClassFile(*objectClassName);

                constantPool = objectClassFile.getConstantPool();
                vector<MethodInfo> methods = objectClassFile.getMethods();

                for (int i = 0; i < objectClassFile.getMethodsCount() && !foundMethod; i++) {
                    method = methods[i];
                    uint16_t nameIndex = method.name_index;
                    uint16_t descriptorIndex = method.descriptor_index;
                    string name = constantPool[nameIndex-1].getInfo(constantPool);
                    string methodDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
                    if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                        foundMethod = true;
                    }
                }

                if (!foundMethod) {
                    if (objectClassFile.getSuperClass() == 0) {
                        printf("invokevirutal:  metodo nao foi encontrado em nenhuma superclasse! Talvez esteja em uma interface, falta Implementar!\n");
                        exit(0);
                    }
                    className = constantPool[objectClassFile.getSuperClass()-1].getInfo(constantPool);
                }
            } while(!foundMethod);
        }

        Frame staticMethodFrame(constantPool, method, frame->jvmStack);

        int argCnt = 1;

        for (int i = 1; descriptor[i] != ')'; i++) {
            if (descriptor[i] == 'I' || descriptor[i] == 'F') {
                Type arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt++;
            }
            else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
                Type arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt+=2;
            }
            else if (descriptor[i] == 'L') {
                int j = i;
                while (descriptor[i] != ';') {
                    i++;
                }
                Type arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt++;
            }
            else if (descriptor[i] == '[') {
                while (descriptor[i] == '[') {
                    i++;
                }
                if (descriptor[i] == 'L') {
                    while (descriptor[i] != ';') {
                        i++;
                    }
                }

                Type arg = auxstack.top();
                auxstack.pop();
                staticMethodFrame.localVariables[argCnt] = arg;
                argCnt++;
            }
            else {
                cout << "Tipo de descritor nao reconhecido: " << descriptor[i] << endl;
                exit(0);
            }
        }
        staticMethodFrame.localVariables[0] = objectref;

        frame->jvmStack->push(staticMethodFrame);
        frame->local_pc++;
        return staticMethodFrame.local_pc;
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
    vector<MethodInfo
    > methods = classfile.getMethods();
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
            newFrame.localVariables[i+1] = auxstack.top();
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
// uint32_t Instruction::invokeinterface(Frame* frame){
// }
//
// uint32_t Instruction::invokedynamic(Frame* frame){
// }
//
uint32_t Instruction::new_func(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    string className = frame->constantPool[index-1].getInfo(frame->constantPool);
    if (className.compare("java/lang/String") == 0 || className.compare("java/lang/StringBuilder") == 0) {
        Type object;
        object.type_reference = (uint64_t)new string("");
        object.tag = TAG_REFERENCE;
        frame->operandStack.push(object);
    } else {
        classLoader->loadClassFile(className);
        MethodArea * methodArea = classLoader->methodArea;
        ClassFile classFile = methodArea->getClassFile(className);
        Type object;
        object.tag = TAG_REFERENCE;
        object.type_reference = (uint64_t)instantiateFields(classFile);
        frame->operandStack.push(object);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::invokespecial(Frame * frame) {
    uint8_t* bytecode
    = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string methodInfo = frame->constantPool[index-1].getInfo(frame->constantPool);
    tuple<string, string, string> methodtuple;
    methodtuple = methodInfoSplit(methodInfo);
    string className = get<0>(methodtuple);
    string methodName = get<1>(methodtuple);
    string descriptor = get<2>(methodtuple);

    if (className.compare("java/lang/String") == 0) {
        if (methodName.compare("<init>") == 0) {
            string* stringReference = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            string* initStringReference = (string*)(frame->operandStack.top().type_reference);
            frame->operandStack.pop();
            *initStringReference = *stringReference;
        }
        else {
            printf("Encontrei esse método ai não %s\n", methodName.c_str());
            exit(0);
        }
        return ++frame->local_pc;
    }
    if (className.compare("java/lang/StringBuilder") == 0) {
        if (methodName.compare("<init>") == 0) {
            frame->operandStack.pop();
        }
        return ++frame->local_pc;
    }

    bool foundMethod = false;
    vector<CPInfo> constantPool;
    MethodInfo method;
    while(!foundMethod) {
        MethodArea * methodArea = classLoader->methodArea;
        ClassFile classFile = methodArea->getClassFile(className);
        constantPool = classFile.getConstantPool();
        vector<MethodInfo> methods = classFile.getMethods();

        for (int i = 0; i < classFile.getMethodsCount() && !foundMethod; i++) {
            method = methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = constantPool[nameIndex-1].getInfo(constantPool);
            string methodDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
            if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                foundMethod = true;
            }
        }

        if (!foundMethod) {
            if (classFile.getSuperClass() == 0) {
                printf("invokespecial: metodo nao foi encontrado em nenhuma superclasse! Talvez esteja em uma interface, falta Implementar!\n");
            }
            string className = constantPool[classFile.getSuperClass()-1].getInfo(constantPool);
        }
    }

    Frame staticMethodFrame(constantPool, method, frame->jvmStack);

    stack<Type> auxstack;

    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
        }
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
        }
        else if (descriptor[i] == 'L') {
            while (descriptor[i] != ';') {
                i++;
            }
        }
        else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
                i++;
            }
            if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
        }
        else {
            cout << "Tipo de descritor nao reconhecido na contagem: " << descriptor[i] << endl;
            exit(0);
        }
        auxstack.push(frame->operandStack.top());
        frame->operandStack.pop();
    }
    int argCnt = 1;
    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            Type arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }

        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            Type arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt += 1;
        }
        else if (descriptor[i] == 'L') {
            int j = i;
            while (descriptor[i] != ';') {
                i++;
            }
            Type arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else if (descriptor[i] == '[') {
            while (descriptor[i] == '[') {
                i++;
            }
            if (descriptor[i] == 'L') {
                while (descriptor[i] != ';') {
                    i++;
                }
            }
            Type arg = auxstack.top();
            auxstack.pop();
            staticMethodFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else {
            cout << "Tipo de descritor nao reconhecido: " << descriptor[i] << endl;
            exit(0);
        }
    }
    Type objectref = frame->operandStack.top();
    frame->operandStack.pop();
    staticMethodFrame.localVariables[0] = objectref;

    frame->jvmStack->push(staticMethodFrame);
    frame->local_pc++;
    return staticMethodFrame.local_pc;
}

uint32_t Instruction::putfield(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string fieldInfo = frame->constantPool[index-1].getInfo(frame->constantPool);
    tuple<string, string, string> fieldtuple;
    fieldtuple = fieldInfoSplit(fieldInfo);
    string className = get<0>(fieldtuple);
    string fieldName = get<1>(fieldtuple);
    string descriptor = get<2>(fieldtuple);

    Type value = frame->operandStack.top();
    frame->operandStack.pop();
    Type objectref = frame->operandStack.top();
    frame->operandStack.pop();

    map<string, Type>* object = (map<string, Type>*)objectref.type_reference;
    object->at(fieldName) = value;

    return ++frame->localPC;
}

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

    if (arrayref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

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
