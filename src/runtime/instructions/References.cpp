#include "../../../include/runtime/instructions/Instruction.hpp"

uint32_t Instruction::newarray(Frame *frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t atype = bytecode[++frame->local_pc];
    int count = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if (count < 0) {
        ExceptionThrower::negativeArraySizeException();
    }

    vector<Type>* arr_type = new vector<Type>(count);

    Type *value;
    value = (Type*)malloc(sizeof(Type));


    if (atype == T_BOOLEAN) {
        value->tag = TAG_INT;
        value->type_int = 0;
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
        value->tag = TAG_INT;
        value->type_int = 0;
    }  else if (atype == T_SHORT) {
        value->tag = TAG_INT;
        value->type_int = 0;
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

    // Type res = frame->operandStack.top();
    // vector<Type>* arrayPointer = (vector<Type>*)res.type_reference;

    return ++frame->local_pc;
}

uint32_t Instruction::getstatic(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];

    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string fieldstring = frame->constantPool[index-1].getInfo(frame->constantPool);
    tuple<string, string, string>fieldtuple = fieldInfoSplit(fieldstring);
    string className = get<0>(fieldtuple);
    string fieldName = get<1>(fieldtuple);
    string descriptorAux = get<2>(fieldtuple);

    if (className.compare("java/lang/System") == 0) {
        return ++frame->local_pc;
    } else {
        ClassFile * classFile = classLoader->methodArea->getClassFile(className);
        vector<CPInfo> constantPool = classFile->getConstantPool();
        vector<MethodInfo> methods = classFile->getMethods();
        MethodInfo method;

        bool foundClinit = false;
        for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
            method = methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = constantPool[nameIndex-1].getInfo(constantPool);
            string classDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
            if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
                foundClinit = true;
            }
        }

        if (foundClinit) {
            Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
            frame->jvmStack->push(clinitMethodFrame);
            frame->local_pc -= 2;
            return clinitMethodFrame.local_pc;
        }
    }

    classLoader->loadClassFile(className);
    ClassFile * classFile = classLoader->methodArea->getClassFile(className);
    vector<CPInfo> constantPool = classFile->getConstantPool();
    vector<FieldInfo*> fields = classFile->getFieldsPointer();
    FieldInfo* field;
    bool foundField = false;
    string descriptor;

    for (int i = 0; i < classFile->getFieldsCount() && !foundField; i++) {
        field = fields[i];
        uint16_t nameIndex = field->name_index;
        uint16_t descriptorIndex = field->descriptor_index;
        string name = constantPool[nameIndex-1].getInfo(constantPool);
        descriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
        if (name.compare(fieldName) == 0 && descriptor.compare(descriptorAux) == 0) {
            foundField = true;
        }
    }

    if (!foundField) {
        printf("getstatic: o field especificado nao pode ser resolvido! Deve estar em uma superclasse ou superinterface! Falta implementar!\n");
        exit(0);
    }

    if (descriptor.compare("C") == 0) {
        frame->operandStack.push(field->static_value);
    }
    else if (descriptor.compare("I") == 0) {
        frame->operandStack.push(field->static_value);
    }
    else if (descriptor.compare("F") == 0) {
        frame->operandStack.push(field->static_value);
    }
    else if (descriptor.compare("D") == 0) {
        frame->operandStack.push(field->static_value);
    }
    else if (descriptor.compare("J") == 0) {
        frame->operandStack.push(field->static_value);
    }
    else if (descriptor.compare("Z") == 0) {
        frame->operandStack.push(field->static_value);
    }
    else if (descriptor[0] == '[') {
        frame->operandStack.push(field->static_value);
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
                cout << *stringReference << isendl;
                frame->operandStack.pop();
            } else if (descriptor.compare("(I)V") == 0){
                cout << frame->operandStack.top().type_int << isendl;
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
                cout << endl;
            } else if (descriptor.compare("(Z)V") == 0){
                cout << frame->operandStack.top().type_int << isendl;
                frame->operandStack.pop();
            }
        }
    } else if (className.compare("java/lang/StringBuilder") == 0 || className.compare("java/lang/StringBuffer") == 0) {
        if (methodName.compare("append") == 0) {
            if (descriptor.compare("(Ljava/lang/String;)Ljava/lang/StringBuilder;") == 0 ||
                descriptor.compare("(Ljava/lang/String;)Ljava/lang/StringBuffer;") == 0) {

                string* str1 = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();
                string* str2 = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                Type objectref;
                objectref.tag = TAG_REFERENCE;
                objectref.type_reference = (uint64_t)new string(*str2 + *str1);
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(I)Ljava/lang/StringBuilder;") == 0 ||
                     descriptor.compare("(I)Ljava/lang/StringBuffer;") == 0) {
                int32_t integer = (int32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                Type objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(integer));
                objectref.tag = TAG_REFERENCE;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(J)Ljava/lang/StringBuilder;") == 0 ||
                     descriptor.compare("(J)Ljava/lang/StringBuffer;") == 0) {

                int64_t longNumber = (int64_t)(frame->operandStack.top().type_long);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                Type objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(longNumber));
                objectref.tag = TAG_REFERENCE;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(F)Ljava/lang/StringBuilder;") == 0 ||
                     descriptor.compare("(F)Ljava/lang/StringBuffer;") == 0) {

                uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                float floatNumber;
                memcpy(&floatNumber, &integer, sizeof(float));

                Type objectref;
                objectref.tag = TAG_REFERENCE;
                objectref.type_reference = (uint64_t)new string(*str + to_string(floatNumber));
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(D)Ljava/lang/StringBuilder;") == 0 ||
                     descriptor.compare("(D)Ljava/lang/StringBuffer;") == 0) {

                uint64_t longNumber = (uint64_t)(frame->operandStack.top().type_double);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                double doubleNumber;
                memcpy(&doubleNumber, &longNumber, sizeof(double));

                Type objectref;
                objectref.type_reference = (uint64_t)new string(*str + to_string(doubleNumber));
                objectref.tag = TAG_REFERENCE;
                frame->operandStack.push(objectref);
            }
            else if (descriptor.compare("(Z)Ljava/lang/StringBuilder;") == 0 ||
                     descriptor.compare("(Z)Ljava/lang/StringBuffer;") == 0) {

                uint32_t integer = (uint32_t)(frame->operandStack.top().type_int);
                frame->operandStack.pop();
                string* str = (string*)(frame->operandStack.top().type_reference);
                frame->operandStack.pop();

                Type objectref;
                if (integer == 1) {
                    objectref.type_reference = (uint64_t)new string(*str + "true");
                }
                else if (integer == 0) {
                    objectref.type_reference = (uint64_t)new string(*str + "false");
                }
                else {
                    cout << "Erro no tipo booleano durante a concatenacao!";
                    exit(0);
                }
                objectref.tag = TAG_REFERENCE;
                frame->operandStack.push(objectref);
            }
            else {
                printf("invokevirtual: descritor nao reconhecido: %s\n", descriptor.c_str());
                exit(0);
            }
        } else if (methodName.compare("toString") == 0) {
            } else {
                printf("invokevirtualFunction: Metodo do StringBuilder nao reconhecido: %s\n", methodName.c_str());
                exit(0);
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
        ClassFile * objectClassFile = classLoader->methodArea->getClassFile(*objectClassName);

        constantPool = objectClassFile->getConstantPool();
        vector<MethodInfo> methods = objectClassFile->getMethods();

        MethodInfo method;
        for (int i = 0; i < objectClassFile->getMethodsCount() && !foundMethod; i++) {
            method = methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = constantPool[nameIndex-1].getInfo(constantPool);
            string methodDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
            if (name.compare(methodName) == 0 && methodDescriptor.compare(descriptor) == 0) {
                foundMethod = true;
            }
        }

        string className = *objectClassName;
        if (!foundMethod) {
            do {
                classLoader->loadClassFile(className);
                MethodArea * methodArea = classLoader->methodArea;
                ClassFile * objectClassFile = methodArea->getClassFile(className);

                constantPool = objectClassFile->getConstantPool();
                vector<MethodInfo> methods = objectClassFile->getMethods();

                for (int i = 0; i < objectClassFile->getMethodsCount() && !foundMethod; i++) {
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
                    if (objectClassFile->getSuperClass() == 0) {
                        printf("invokevirtual:  metodo nao foi encontrado\n");
                        exit(0);
                    }
                    className = constantPool[objectClassFile->getSuperClass()-1].getInfo(constantPool);
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
                // int j = i;
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

uint32_t Instruction::getfield(Frame * frame) {
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

    Type objectref = frame->operandStack.top();
    frame->operandStack.pop();
    if (objectref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    map<string, Type>* object = (map<string, Type>*)objectref.type_reference;
    Type value = object->at(fieldName);

    frame->operandStack.push(value);

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

    ClassFile * classfile = classLoader->methodArea->getClassFile(className);
    vector<MethodInfo> methods = classfile->getMethods();
    int i;
    for (i = 0; i < classfile->getMethodsCount(); i++) {
        if(methods[i].name == methodName && methods[i].descriptor == descriptor) {
            break;
        }
    }
    Frame newFrame(frame->constantPool, methods[i], frame->jvmStack);

    // Empilha os argumentos para reverter a ordem
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
    int argCnt = 0;
    for (int i = 1; descriptor[i] != ')'; i++) {
        if (descriptor[i] == 'I' || descriptor[i] == 'F') {
            Type arg = auxstack.top();
            auxstack.pop();
            newFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else if (descriptor[i] == 'J' || descriptor[i] == 'D') {
            Type arg = auxstack.top();
            auxstack.pop();
            newFrame.localVariables[argCnt] = arg;
            argCnt += 2;
        }
        else if (descriptor[i] == 'L') {
            // int j = i;
            while (descriptor[i] != ';') {
                i++;
            }
            Type arg = auxstack.top();
            auxstack.pop();
            newFrame.localVariables[argCnt] = arg;
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
            newFrame.localVariables[argCnt] = arg;
            argCnt++;
        }
        else {
            cout << "Tipo de descritor nao reconhecido: " << descriptor[i] << endl;
            exit(0);
        }
    }

    frame->jvmStack->push(newFrame);
    ++frame->local_pc;
    return newFrame.local_pc;
}

uint32_t Instruction::putstatic(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    string fieldstring = frame->constantPool[index-1].getInfo(frame->constantPool);
    tuple<string, string, string>fieldtuple = fieldInfoSplit(fieldstring);
    string className = get<0>(fieldtuple);
    string fieldName = get<1>(fieldtuple);
    string descriptorAux = get<2>(fieldtuple);

    classLoader->loadClassFile(className);
    ClassFile * classFile = classLoader->methodArea->getClassFile(className);
    vector<CPInfo> constantPool = classFile->getConstantPool();
    vector<MethodInfo> methods = classFile->getMethods();
    MethodInfo method;

    bool foundClinit = false;
    for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
        method = methods[i];
        uint16_t nameIndex = method.name_index;
        uint16_t descriptorIndex = method.descriptor_index;
        string name = constantPool[nameIndex-1].getInfo(constantPool);
        string classDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
        if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
            foundClinit = true;
        }
    }

    if (foundClinit) {
        Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
        frame->jvmStack->push(clinitMethodFrame);
        frame->local_pc-=2;
        return clinitMethodFrame.local_pc;
    }

    classLoader->loadClassFile(className);
    classFile = classLoader->methodArea->getClassFile(className);
    constantPool = classFile->getConstantPool();
    vector<FieldInfo*> fields = classFile->getFieldsPointer();
    FieldInfo* field;
    bool foundField = false;

    for (int i = 0; i < classFile->getFieldsCount() && !foundField; i++) {
        field = fields[i];
        uint16_t nameIndex = field->name_index;
        uint16_t descriptorIndex = field->descriptor_index;
        string name = constantPool[nameIndex-1].getInfo(constantPool);
        string descriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
        if (name.compare(fieldName) == 0 && descriptor.compare(descriptorAux) == 0) {
            foundField = true;
        }
    }

    if (!foundField) {
        printf("putstatic: o field especificado nao pode ser resolvido! Deve estar em uma superclasse ou superinterface! Falta implementar!\n");
        exit(0);
    }

    if (descriptorAux.compare("C") == 0) {
        field->static_value.tag = TAG_CHAR;
        field->static_value.type_char = frame->operandStack.top().type_char;
        frame->operandStack.pop();
    }
    else if (descriptorAux.compare("I") == 0) {
        field->static_value.tag = TAG_INT;
        field->static_value.type_int = frame->operandStack.top().type_int;
        frame->operandStack.pop();
    }
    else if (descriptorAux.compare("F") == 0) {
        field->static_value.tag = TAG_FLOAT;
        field->static_value.type_float = frame->operandStack.top().type_float;
        frame->operandStack.pop();
    }
    else if (descriptorAux.compare("D") == 0) {
        field->static_value.tag = TAG_DOUBLE;
        field->static_value.type_double = frame->operandStack.top().type_double;
        frame->operandStack.pop();
    }
    else if (descriptorAux.compare("J") == 0) {
        field->static_value.tag = TAG_LONG;
        field->static_value.type_long = frame->operandStack.top().type_long;
        frame->operandStack.pop();
    }
    else if (descriptorAux.compare("Z") == 0) {
        field->static_value.tag = TAG_INT;
        field->static_value.type_int = frame->operandStack.top().type_int;
        frame->operandStack.pop();
    }
    else if (descriptorAux[0] == '[') {
        field->static_value.tag = TAG_REFERENCE;
        field->static_value.type_reference = frame->operandStack.top().type_reference;
        frame->operandStack.pop();
    }
    else {
        printf("putstatic: tipo do descritor nao reconhecido: %s\n", descriptorAux.c_str());
        exit(0);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::new_func(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    uint16_t index = ((uint16_t)byte1 << 8) | byte2;
    string className = frame->constantPool[index-1].getInfo(frame->constantPool);
    if (className.compare("java/lang/String") == 0 ||
        className.compare("java/lang/StringBuilder") == 0 ||
        className.compare("java/lang/StringBuffer") == 0) {

        Type object;
        object.type_reference = (uint64_t)new string("");
        object.tag = TAG_REFERENCE;
        frame->operandStack.push(object);
    } else {

        classLoader->loadClassFile(className);
        ClassFile * classFile = classLoader->methodArea->getClassFile(className);
        vector<CPInfo> constantPool = classFile->getConstantPool();
        vector<MethodInfo> methods = classFile->getMethods();
        MethodInfo method;

        bool foundClinit = false;
        for (int i = 0; i < classFile->getMethodsCount() && !foundClinit; i++) {
            method = methods[i];
            uint16_t nameIndex = method.name_index;
            uint16_t descriptorIndex = method.descriptor_index;
            string name = constantPool[nameIndex-1].getInfo(constantPool);
            string classDescriptor = constantPool[descriptorIndex-1].getInfo(constantPool);
            if (name.compare("<clinit>") == 0 && classDescriptor.compare("()V") == 0) {
                foundClinit = true;
            }
        }

        if (foundClinit) {
            Frame clinitMethodFrame(constantPool, method, frame->jvmStack);
            frame->jvmStack->push(clinitMethodFrame);
            frame->local_pc -= 2;
            return clinitMethodFrame.local_pc;
        }

        classLoader->loadClassFile(className);
        classFile = classLoader->methodArea->getClassFile(className);
        Type object;
        object.tag = TAG_REFERENCE;
        object.type_reference = (uint64_t)instantiateFields(classFile);
        frame->operandStack.push(object);
    }

    return ++frame->local_pc;
}

uint32_t Instruction::invokespecial(Frame * frame) {
    uint8_t* bytecode = frame->codeAttribute.code;
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
    if (className.compare("java/lang/StringBuilder") == 0 ||
        className.compare("java/lang/StringBuffer") == 0) {
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
        ClassFile * classFile = methodArea->getClassFile(className);
        constantPool = classFile->getConstantPool();
        vector<MethodInfo> methods = classFile->getMethods();

        for (int i = 0; i < classFile->getMethodsCount() && !foundMethod; i++) {
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
            if (classFile->getSuperClass() == 0) {
                printf("invokespecial: metodo nao foi encontrado em nenhuma superclasse! Talvez esteja em uma interface, falta Implementar!\n");
            }
            string className = constantPool[classFile->getSuperClass()-1].getInfo(constantPool);
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
            argCnt += 2;
        }
        else if (descriptor[i] == 'L') {
            // int j = i;
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

    if (objectref.type_reference == (uint64_t)NULL) {
        ExceptionThrower::nullPointerException();
    }

    map<string, Type>* object = (map<string, Type>*)objectref.type_reference;
    object->at(fieldName) = value;

    return ++frame->local_pc;
}

uint32_t Instruction::anewarray(Frame* frame){
    uint8_t* bytecode = frame->codeAttribute.code;
    uint8_t byte1 = bytecode[++frame->local_pc];
    uint8_t byte2 = bytecode[++frame->local_pc];
    // uint16_t index = ((uint16_t)byte1 << 8) | byte2;

    int count = frame->operandStack.top().type_int;
    frame->operandStack.pop();

    if (count < 0) {
        ExceptionThrower::negativeArraySizeException();
    }

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

uint32_t Instruction::athrow(Frame* frame){
    Type objectref = frame->operandStack.top();
    frame->operandStack.pop();

    return ++frame->local_pc;
}

uint32_t Instruction::invokeinterface(Frame* frame){
    ExceptionThrower::instructionNotImplemented(0);
    return ++frame->local_pc;
}

uint32_t Instruction::invokedynamic(Frame* frame){
    ExceptionThrower::instructionNotImplemented(0);
    return ++frame->local_pc;
}

uint32_t Instruction::checkcast(Frame* frame){
    ExceptionThrower::instructionNotImplemented(0);
    return ++frame->local_pc;
}

uint32_t Instruction::instanceof(Frame* frame){
    ExceptionThrower::instructionNotImplemented(0);
    return ++frame->local_pc;
}

uint32_t Instruction::monitorenter(Frame* frame){
    ExceptionThrower::instructionNotImplemented(0);
    return ++frame->local_pc;
}

uint32_t Instruction::monitorexit(Frame* frame){
    ExceptionThrower::instructionNotImplemented(0);
    return ++frame->local_pc;
}
