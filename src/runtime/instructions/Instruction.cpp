#include "../../../include/runtime/instructions/Instruction.hpp"

/** \file Instruction.cpp
 *
 *
 */

Instruction::Instruction() { }

Instruction::Instruction(string opcode_name) {
    this->mnemonic = opcode_name;
}

Instruction::Instruction(string opcode_name, uint32_t bytecount) {
    this->classLoader = classLoader;
    this->mnemonic = opcode_name;
    this->bytecount = bytecount;
}

tuple<string, string, string>Instruction::methodInfoSplit(string methodinfo) {
    int j = 0;
    int w = 0;

    while (w < methodinfo.size() && methodinfo[w+1] != '#') {
        w++;
    }
    string className = methodinfo.substr(0,w+1);
    string nameAndType = methodinfo.substr(w+2, methodinfo.size());
    while (j < nameAndType.size() && nameAndType[j+1] != '$') {
        j++;
    }
    string methodName = nameAndType.substr(0,j+1);
    string descriptor = nameAndType.substr(j+2,nameAndType.size());

    return make_tuple(className, methodName, descriptor);
}

tuple<string, string, string>Instruction::fieldInfoSplit(string fieldInfo) {
    int j = 0;
    int w = 0;
    while (w < fieldInfo.size() && fieldInfo[w+1] != '#') {
        w++;
    }
    string className = fieldInfo.substr(0,w+1);
    string nameAndType = fieldInfo.substr(w+2, fieldInfo.size());
    while (j < nameAndType.size() && nameAndType[j+1] != '$') {
        j++;
    }
    string fieldName = nameAndType.substr(0,j+1);
    string descriptor = nameAndType.substr(j+2,nameAndType.size());

    return make_tuple(className, fieldName, descriptor);
}

map<string, Type>* Instruction::instantiateFields(ClassFile * classFile) {
    map<string, Type>* object = new map<string, Type>;
    ClassFile * objectClassFile = classFile;
    do {
        vector<CPInfo> constantPool = classFile->getConstantPool();
        vector<FieldInfo> fields = classFile->getFields();
        for (int i = 0; i < classFile->getFieldsCount(); i++) {

            CPInfo fieldInfo = constantPool[fields[i].name_index-1];
            CPInfo descriptorInfo = constantPool[fields[i].descriptor_index-1];
            string fieldName = fieldInfo.getInfo(constantPool);
            string descriptor = descriptorInfo.getInfo(constantPool);

            Type fieldContent;

            if (descriptor.compare("C") == 0) {
                fieldContent.tag = TAG_CHAR;
                fieldContent.type_char = 0;
            }
            else if (descriptor.compare("I") == 0) {
                fieldContent.tag = TAG_INT;
                fieldContent.type_int = 0;
            }
            else if (descriptor.compare("F") == 0) {
                fieldContent.tag = TAG_FLOAT;
                fieldContent.type_float = 0;
            }
            else if (descriptor.compare("D") == 0) {
                fieldContent.tag = TAG_DOUBLE;
                fieldContent.type_double = 0.0;
            }
            else if (descriptor.compare("J") == 0) {
                fieldContent.tag = TAG_LONG;
                fieldContent.type_long = 0;
            }
            else if (descriptor.compare("Z") == 0) {
                fieldContent.tag = TAG_BOOL;
                fieldContent.type_boolean = false;
            }
            else if (descriptor[0] == 'L') {
                fieldContent.tag = TAG_REFERENCE;
                fieldContent.type_reference = (uint64_t)NULL;
            }
            else if (descriptor[0] == '[') {
                fieldContent.tag = TAG_REFERENCE;
                fieldContent.type_reference = (uint64_t)NULL;
            }
            else {
                printf("Sei que field é esse não: %s\n", descriptor.c_str());
                exit(0);
            }

            object->insert(make_pair(fieldName, fieldContent));
        }

        string superClassName = constantPool[classFile->getSuperClass()-1].getInfo(constantPool);
        classLoader->loadClassFile(superClassName);
        classFile = classLoader->methodArea->getClassFile(superClassName);
    } while (classFile->getSuperClass() != 0);

    Type thisClass;
    uint16_t thisClassIndex = objectClassFile->getThisClass();
    CPInfo thisClassInfo = objectClassFile->getConstantPool()[thisClassIndex-1];
    string thisClassName = thisClassInfo.getInfo(objectClassFile->getConstantPool());
    thisClass.tag = TAG_REFERENCE;
    thisClass.type_reference = (uint64_t)new string(thisClassName);
    object->insert(make_pair("<this_class>", thisClass));
    return object;
}
