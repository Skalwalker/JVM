#ifndef __CPINFO_H__
#define __CPINFO_H__
#include <cstdint>
#include <fstream>
#include "ClassFileReader.hpp"

#define typeof __typeof__

#define CONSTANT_CLASS 7
#define CONSTANT_FIELD_REF 9
#define CONSTANT_METHOD_REF 10
#define CONSTANT_INTERFACE_METHOD_REF 11
#define CONSTANT_STRING 8
#define CONSTANT_INTEGER 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6
#define CONSTANT_NAME_AND_TYPE 12
#define CONSTANT_UTF8 1
#define CONSTANT_METHOD_HANDLE 15
#define CONSTANT_METHOD_TYPE 16
#define CONSTANT_INVOKE_DYNAMIC 18

// Definicao dos tipos de info que podem existir em CPinfo: pág 78 jvm
typedef struct {
    uint16_t name_index;
} CONSTANT_Class_info;

typedef struct {
    uint16_t class_index;
    uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct {
    uint16_t class_index;
    uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct {
    uint16_t class_index;
    uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct {
    uint16_t string_index;
} CONSTANT_String_info;

typedef struct {
    uint32_t bytes;
} CONSTANT_Integer_info;

typedef struct {
    uint32_t bytes;
} CONSTANT_Float_info;

typedef struct {
    uint32_t high_bytes;
    uint32_t low_bytes;
} CONSTANT_Long_info;

typedef struct {
    uint32_t high_bytes;
    uint32_t low_bytes;
} CONSTANT_Double_info;

typedef struct {
    uint16_t name_index;
    uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct {
    uint16_t length;
    uint8_t *bytes;
} CONSTANT_Utf8_info;

typedef struct {
    uint8_t reference_kind;
    uint16_t reference_index;
} CONSTANT_MethodHandle_info;

typedef struct {
    uint16_t descriptor_index;
} CONSTANT_MethodType_info;

typedef struct {
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
} CONSTANT_InvokeDynamic_info;

class CPInfo {
public:
    uint8_t tag;
    std::string name;
    // Somente declarado para mostrar que é um vetor de bytes no DOC da jvm
    // uint8_t info[];
    // info tem tamanho variável. union se mostra uma boa escolha. Ladeira gosta
    union {
        CONSTANT_Class_info classInfo;
        CONSTANT_Fieldref_info fieldRefInfo;
        CONSTANT_Methodref_info methodRefInfo;
        CONSTANT_InterfaceMethodref_info interfaceMethodRef;
        CONSTANT_String_info stringInfo;
        CONSTANT_Integer_info integerInfo;
        CONSTANT_Float_info floatInfo;
        CONSTANT_Long_info longInfo;
        CONSTANT_Double_info doubleInfo;
        CONSTANT_NameAndType_info nameAndTypeInfo;
        CONSTANT_Utf8_info utf8Info;
        CONSTANT_MethodHandle_info methodHandleInfo;
        CONSTANT_MethodType_info methodTypeInfo;
        CONSTANT_InvokeDynamic_info invokeDynamicInfo;
    };
    CPInfo();
    CPInfo(uint8_t tag, FILE * fp);
};

#endif
