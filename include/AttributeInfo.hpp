#include <vector>

typedef struct {
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_pc;

} Exception_table;

typedef struct {
    uint16_t start_pc;
    uint16_t line_number;

} Line_number_table;

typedef struct {
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t signature_index;
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
} Classe;

typedef struct {
    uint16_t name_index;
    uint16_t access_flags;
} Parameter;

class ConstantValueAttribute {
public:
    uint16_t valueIndex;
};

class CodeAttribute {
public:
    uint16_t maxStack;
    uint16_t maxLocals;
    uint32_t codeLengths;
    uint8_t * code;
    uint16_t exceptionTableLength;
    Exception_table * exceptionTable;
    uint16_t attributesCount;
};

class ExceptionsAttribute {
public:
    uint16_t numberOfExceptions;
    uint16_t * exception_index_table;
};

class InnerClassesAttribute {
    Classe * classes;
};

class EnclosingMethodAttribute {
    uint16_t classIndex;
    uint16_t methodIndex;
};

class SyntheticAttribute {
};

class SourceFileAttribute {
    uint16_t sourceFileIndex;
};

class SignatureAttribute {
    uint16_t signatureIndex;
};

class LineNumberTableAttribute {
    uint16_t lineNumberTableLength;
    Line_number_table * LineNumberTable;
};

class LocalVariableTableAttribute {
    uint16_t localVariableTableLength;
    Local_variable_table * localVariableTypeTable;
};

class LocalVariableTypeTableAttribute {
    uint16_t localVariableTypeTableLength;
    Local_variable_type_table * localVariableTypeTable;
};

class MethodParameters {
    uint16_t attributeNameIndex;
    uint32_t attributeLength;
    uint8_t parameters_count;
    Parameter * parameters;
};

class AttributeInfo {
    uint16_t attributeNameIndex;
    uint32_t attributeLength;
    union {
        ConstantValueAttribute constantValue;
        CodeAttribute code;
        ExceptionsAttribute exceptions;
        InnerClassesAttribute innerClasses;
        EnclosingMethodAttribute enclosingMethod;
        SyntheticAttribute synthetic;
        SourceFileAttribute sourceFile;
        SignatureAttribute signarute;
        LineNumberTableAttribute lineNumberTable;
        LocalVariableTableAttribute localVariableTable;
        LocalVariableTypeTableAttribute localVariableTypeTable;
        MethodParameters methodParameters;
    };
    AttributeInfo();
};
