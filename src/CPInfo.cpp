#include "../include/CPInfo.hpp"

CPInfo::CPInfo(uint8_t tag, FILE * fp) {
    // oneByte e twoBytes criadas para diminuir a verbosidade
    uint8_t oneByte;
    uint16_t twoBytes;

    this->tag = tag;
    if (tag == CONSTANT_CLASS) {
        ClassFileReader<typeof(twoBytes)> name_index;
        this->classInfo.name_index = name_index.readBytes(fp);

    } else if (tag == CONSTANT_METHOD_REF) {
        ClassFileReader<typeof(twoBytes)> class_index;
        this->methodRefInfo.class_index = class_index.readBytes(fp);

        ClassFileReader<typeof(twoBytes)> name_and_type_index;
        this->methodRefInfo.name_and_type_index = name_and_type_index.readBytes(fp);

    } else if (tag == CONSTANT_FIELD_REF) {
        ClassFileReader<typeof(twoBytes)> class_index;
        this->fieldRefInfo.class_index = class_index.readBytes(fp);

        ClassFileReader<typeof(twoBytes)> name_and_type_index;
        this->fieldRefInfo.name_and_type_index = name_and_type_index.readBytes(fp);

    } else if (tag == CONSTANT_STRING) {
        ClassFileReader<typeof(twoBytes)> string_index;
        this->stringInfo.string_index = string_index.readBytes(fp);

    } else if (tag == CONSTANT_UTF8) {
        ClassFileReader<typeof(twoBytes)> length;
        ClassFileReader<typeof(oneByte)> stringByte;
        this->utf8Info.length = length.readBytes(fp);
        // calloc inicializa a memória com zero, diferentemente do malloc
        this->utf8Info.bytes = (uint8_t *) calloc(this->utf8Info.length+1, sizeof(uint8_t));
        for (int byte = 0; byte < this->utf8Info.length; byte++) {
            this->utf8Info.bytes[byte] = stringByte.readBytes(fp);
        }
        this->utf8Info.bytes[this->utf8Info.length] = '\0';

    } else if (tag == CONSTANT_NAME_AND_TYPE) {
        ClassFileReader<typeof(twoBytes)> name_index;
        ClassFileReader<typeof(twoBytes)> descriptor_index;
        this->nameAndTypeInfo.name_index = name_index.readBytes(fp);
        this->nameAndTypeInfo.descriptor_index = descriptor_index.readBytes(fp);
    } else {
        printf("não passei em nenhum\n");
    }
}
