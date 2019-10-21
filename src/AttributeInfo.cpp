#include "../include/AttributeInfo.hpp"

ClassFileReader<uint8_t> oneByte;
ClassFileReader<uint16_t> twoBytes;
ClassFileReader<uint32_t> fourBytes;


void SourceFileAttribute::create(FILE * fp) {
    sourceFileIndex = twoBytes.readBytes(fp);
}

void ExceptionsAttribute::create(FILE * fp) {
    numberOfExceptions = twoBytes.readBytes(fp);
    exception_index_table = (uint16_t *) calloc(numberOfExceptions, sizeof(uint16_t));
    for (int excp = 0; excp < numberOfExceptions; excp++) {
        exception_index_table[excp] = twoBytes.readBytes(fp);
    }
}

void LineNumberTableAttribute::create(FILE * fp) {
    lineNumberTableLength = twoBytes.readBytes(fp);
    lineNumberTable = (Line_number_table *)
        calloc(lineNumberTableLength, sizeof(Line_number_table));
    for (int i = 0; i < lineNumberTableLength; i++) {
        lineNumberTable[i].start_pc = twoBytes.readBytes(fp);
        lineNumberTable[i].line_number = twoBytes.readBytes(fp);
    }
}

void LocalVariableTableAttribute::create(FILE * fp) {
    localVariableTableLength = twoBytes.readBytes(fp);
    localVariableTable = (Local_variable_table *)
        calloc(localVariableTableLength, sizeof(Local_variable_table));
    for (int i = 0; i < localVariableTableLength; i++) {
        localVariableTable[i].start_pc = twoBytes.readBytes(fp);
        localVariableTable[i].length = twoBytes.readBytes(fp);
        localVariableTable[i].name_index = twoBytes.readBytes(fp);
        localVariableTable[i].descriptor_index = twoBytes.readBytes(fp);
        localVariableTable[i].index = twoBytes.readBytes(fp);
    }
}

void LocalVariableTypeTableAttribute::create(FILE * fp) {
    localVariableTypeTableLength = twoBytes.readBytes(fp);
    localVariableTypeTable = (Local_variable_type_table *)
        calloc(localVariableTypeTableLength, sizeof(Local_variable_type_table));
    for (int i = 0; i < localVariableTypeTableLength; i++) {
        localVariableTypeTable[i].start_pc = twoBytes.readBytes(fp);
        localVariableTypeTable[i].length = twoBytes.readBytes(fp);
        localVariableTypeTable[i].name_index = twoBytes.readBytes(fp);
        localVariableTypeTable[i].signature_index = twoBytes.readBytes(fp);
        localVariableTypeTable[i].index = twoBytes.readBytes(fp);
    }
}

void CodeAttribute::create(vector<CPInfo> cp, FILE * fp) {
    maxStack = twoBytes.readBytes(fp);
    maxLocals = twoBytes.readBytes(fp);
    codeLength = fourBytes.readBytes(fp);
    code = (uint8_t *) calloc(codeLength, sizeof(uint8_t));
    for (int i = 0; i < codeLength; i++) {
        code[i] = oneByte.readBytes(fp);
    }
    exceptionTableLength = twoBytes.readBytes(fp);
    exceptionTable = (Exception_table *) calloc(exceptionTableLength, sizeof(Exception_table));
    for (int i = 0; i < exceptionTableLength; i++) {
        exceptionTable[i].start_pc = twoBytes.readBytes(fp);
        exceptionTable[i].end_pc = twoBytes.readBytes(fp);
        exceptionTable[i].handler_pc = twoBytes.readBytes(fp);
        exceptionTable[i].catch_type = twoBytes.readBytes(fp);
    }
    attributesCount = twoBytes.readBytes(fp);

    attributes = (AttributeInfo *) calloc(attributesCount, sizeof(AttributeInfo));
    for (int attr = 0; attr < attributesCount; attr++) {
        AttributeInfo attrInfo(cp, fp);
        attributes[attr] = attrInfo;
    }
}

AttributeInfo::AttributeInfo(vector<CPInfo> cp, FILE * fp) {

    attributeNameIndex = twoBytes.readBytes(fp);
    attributeLength = fourBytes.readBytes(fp);
    // o index da cp na jvm vai de 1 a n não de 0 a n-1
    CPInfo utf8 = cp[attributeNameIndex-1];
    string str((char *)utf8.utf8Info.bytes);
    attributeName = str;

    if (attributeName == "Code") {
        cout << "Criando Attribute Code" << endl;
        code.create(cp, fp);

    } else if (attributeName == "LineNumberTable") {
        cout << "Criando Attribute LineNumberTable" << endl;
        lineNumberTable.create(fp);

    } else if (attributeName == "LocalVariableTable") {
        cout << "Criando Attribute LocalVariableTable" << endl;
        localVariableTable.create(fp);

    } else if (attributeName == "LocalVariableTypeTable") {
        cout << "Criando Attribute localVariableTypeTable" << endl;
        localVariableTypeTable.create(fp);

    } else if (attributeName == "Exceptions") {
        cout << "Criando Attribute Exceptions" << endl;
        exceptions.create(fp);

    } else if (attributeName == "SourceFile") {
        cout << "Criando Attribute SourceFile" << endl;
        sourceFile.create(fp);
    }
}
