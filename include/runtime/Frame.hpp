#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include <cstdint>
#include <vector>
#include <stack>
#include "../models/CPInfo.hpp"
#include "../models/MethodInfo.hpp"

#define TAG_EMPTY 0
#define TAG_BOOL 1
#define TAG_BYTE 2
#define TAG_CHAR 3
#define TAG_SHORT 4
#define TAG_INT 5
#define TAG_FLOAT 6
#define TAG_REFERENCE 7
#define TAG_RETURN 8
#define TAG_LONG 9
#define TAG_DOUBLE 10

struct Type {
    uint8_t tag;
    union {
        uint32_t type_empty;
        uint32_t type_boolean;
        uint32_t type_byte;
        uint32_t type_char;
        uint32_t type_short;
        int32_t type_int;
        uint32_t type_float;
        uint64_t type_reference;
        uint32_t type_returnAddress;
        int64_t type_long;
        uint64_t type_double;
    };
};

class Frame {
public:
    MethodInfo method;
    CodeAttribute codeAttribute;
    stack<Type> operandStack;
    vector<Type> localVariables;
    vector<CPInfo> constantPool;
    stack<Frame>* jvmStack;
    uint32_t local_pc;

    Frame(vector<CPInfo>, MethodInfo, stack<Frame>*);
};

#endif
