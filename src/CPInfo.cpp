#include "../include/CPInfo.hpp"

CPInfo::CPInfo(uint8_t tag, FILE * fp) {
    // oneByte e twoBytes criadas para diminuir a verbosidade
    ClassFileReader<uint8_t> oneByte;
    ClassFileReader<uint16_t> twoBytes;
    ClassFileReader<uint32_t> threeBytes;

    this->tag = tag;
    if (tag == CONSTANT_CLASS) {
        this->classInfo.name_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_METHOD_REF) {
        this->methodRefInfo.class_index = twoBytes.readBytes(fp);
        this->methodRefInfo.name_and_type_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_FIELD_REF) {
        this->fieldRefInfo.class_index = twoBytes.readBytes(fp);
        this->fieldRefInfo.name_and_type_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_STRING) {
        this->stringInfo.string_index = twoBytes.readBytes(fp);

    } else if (tag == CONSTANT_UTF8) {
        this->utf8Info.length = twoBytes.readBytes(fp);
        // calloc inicializa a memória com zero, diferentemente do malloc
        this->utf8Info.bytes = (uint8_t *) calloc(this->utf8Info.length+1, sizeof(uint8_t));
        for (int byte = 0; byte < this->utf8Info.length; byte++) {
            this->utf8Info.bytes[byte] = oneByte.readBytes(fp);
        }
        this->utf8Info.bytes[this->utf8Info.length] = '\0';

    } else if (tag == CONSTANT_NAME_AND_TYPE) {
        this->nameAndTypeInfo.name_index = twoBytes.readBytes(fp);
        this->nameAndTypeInfo.descriptor_index = twoBytes.readBytes(fp);
    } else {
        printf("não passei em nenhum\n");
    }
}
