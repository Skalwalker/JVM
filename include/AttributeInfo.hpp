#ifndef __ATTRIBUTEINFO_H__
#define __ATTRIBUTEINFO_H__
#include <vector>
#include <string>
#include <string.h>
#include "CPInfo.hpp"

#define typeof __typeof__

using namespace std;

class AttributeInfo;

typedef struct {
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;

} Exception_table;

typedef struct {
    uint16_t start_pc;
    uint16_t line_number;

} Line_number_table;

typedef struct {
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t index;

} Local_variable_table;

typedef struct {
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t signature_index;
    uint16_t index;

} Local_variable_type_table;

typedef struct {
    uint16_t inner_class_info_index;
    uint16_t outer_class_info_index;
    uint16_t inner_name_index;
    uint16_t inner_class_access_flags;
} Class;

typedef struct {
    uint16_t name_index;
    uint16_t access_flags;
} Parameter;

class ConstantValueAttribute {
public:
    uint16_t valueIndex;
    void create(FILE * fp);
};

class CodeAttribute {
public:
    uint16_t maxStack;
    uint16_t maxLocals;
    uint32_t codeLength;
    uint8_t * code;
    uint16_t exceptionTableLength;
    Exception_table * exceptionTable;
    uint16_t attributesCount;
    AttributeInfo * attributes;
    void create(vector<CPInfo> cp, FILE * fp);
};

class ExceptionsAttribute {
public:
    uint16_t numberOfExceptions;
    uint16_t * exception_index_table;
    void create(FILE * fp);
};

class InnerClassesAttribute {
public:
    uint16_t numberOfClasses;
    Class * classes;
    void create(FILE * fp);
};

class EnclosingMethodAttribute {
    uint16_t classIndex;
    uint16_t methodIndex;
};

class SyntheticAttribute {
public:
    void create(FILE * fp);
};

class SourceFileAttribute {
public:
    uint16_t sourceFileIndex;
    void create(FILE * fp);
};

class SignatureAttribute {
    uint16_t signatureIndex;
public:
    void create(FILE * fp);
};

class LineNumberTableAttribute {
public:
    uint16_t lineNumberTableLength;
    Line_number_table * lineNumberTable;
    void create(FILE * fp);
};

class LocalVariableTableAttribute {
public:
    uint16_t localVariableTableLength;
    Local_variable_table * localVariableTable;
    void create(FILE * fp);
};

class LocalVariableTypeTableAttribute {
public:
    uint16_t localVariableTypeTableLength;
    Local_variable_type_table * localVariableTypeTable;
    void create(FILE * fp);
};

class Deprecated {
public:
    void create(FILE * fp);
};

class MethodParameters {
    uint16_t attributeNameIndex;
    uint32_t attributeLength;
    uint8_t parameters_count;
    Parameter * parameters;
};

class AttributeInfo {
public:
    string attributeName;
    uint16_t attributeNameIndex;
    uint32_t attributeLength;
    uint16_t tag;
    union {
        ConstantValueAttribute constantValue;
        CodeAttribute code;
        ExceptionsAttribute exceptions;
        InnerClassesAttribute innerClasses;
        EnclosingMethodAttribute enclosingMethod; //kd
        SyntheticAttribute synthetic;
        SourceFileAttribute sourceFile;
        SignatureAttribute signarute; //kd
        LineNumberTableAttribute lineNumberTable;
        LocalVariableTableAttribute localVariableTable;
        LocalVariableTypeTableAttribute localVariableTypeTable;
        MethodParameters methodParameters; //kd
        Deprecated deprecated;
    };
    AttributeInfo(vector<CPInfo> cp, FILE * fp);
    AttributeInfo();

};

#endif
