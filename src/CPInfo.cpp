#include "../include/CPInfo.hpp"

CPInfo::CPInfo(uint8_t tag, FILE * fp) {
    // oneByte e twoBytes criadas para diminuir a verbosidade
    ClassFileReader<uint8_t> oneByte;
    ClassFileReader<uint16_t> twoBytes;
    ClassFileReader<uint32_t> fourBytes;
    this->tag = tag;

    if (tag == CONSTANT_CLASS) {
        this->name = "Class Info";
        this->classInfo.name_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_METHOD_REF) {
        this->name = "MethodRef Info";
        this->methodRefInfo.class_index = twoBytes.readBytes(fp);
        this->methodRefInfo.name_and_type_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_FIELD_REF) {
        this->name = "FieldRef Info";
        this->fieldRefInfo.class_index = twoBytes.readBytes(fp);
        this->fieldRefInfo.name_and_type_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_STRING) {
        this->name = "String Info";
        this->stringInfo.string_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_UTF8) {
        this->name = "UTF8 Info";
        this->utf8Info.length = twoBytes.readBytes(fp);
        // calloc inicializa a memória com zero, diferentemente do malloc
        this->utf8Info.bytes = (uint8_t *) calloc(this->utf8Info.length+1, sizeof(uint8_t));
        for (int byte = 0; byte < this->utf8Info.length; byte++) {
            this->utf8Info.bytes[byte] = oneByte.readBytes(fp);
        }
        this->utf8Info.bytes[this->utf8Info.length] = '\0';

    } else if (tag == CONSTANT_NAME_AND_TYPE) {
        this->name = "NameAndType Info";
        this->nameAndTypeInfo.name_index = twoBytes.readBytes(fp);
        this->nameAndTypeInfo.descriptor_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_INTERFACE_METHOD_REF) {
        this->name = "InterfaceMethodRef Info";
        this->interfaceMethodRef.class_index = twoBytes.readBytes(fp);
        this->interfaceMethodRef.name_and_type_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_INTEGER) {
        this->name = "Integer Info";
        this->integerInfo.bytes = fourBytes.readBytes(fp);

    } else if (tag == CONSTANT_FLOAT) {
        this->name = "Float Info";
        this->floatInfo.bytes = fourBytes.readBytes(fp);

    } else if (tag == CONSTANT_LONG) {
        this->name = "Long Info";
        this->longInfo.high_bytes = fourBytes.readBytes(fp);
        this->longInfo.low_bytes = fourBytes.readBytes(fp);

    } else if (tag == CONSTANT_DOUBLE) {
        this->name = "Double Info";
        this->doubleInfo.high_bytes = fourBytes.readBytes(fp);
        this->doubleInfo.low_bytes = fourBytes.readBytes(fp);

    } else if (tag == CONSTANT_METHOD_HANDLE) {
        this->name = "MethodHandle Info";
        this->methodHandleInfo.reference_kind = oneByte.readBytes(fp);
        this->methodHandleInfo.reference_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_METHOD_TYPE) {
        this->name = "MethodType Info";
        this->methodTypeInfo.descriptor_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_INVOKE_DYNAMIC) {
        this->name = "InvokeDynamic Info";
        this->invokeDynamicInfo.bootstrap_method_attr_index = twoBytes.readBytes(fp);
        this->invokeDynamicInfo.name_and_type_index = twoBytes.readBytes(fp);

    } else {
        printf("NDA\n");
    }
}

uint8_t CPInfo::getTag(){
  return this->tag;
}
