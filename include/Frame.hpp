#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include <cstdint>
#include <vector>
#include <stack>
#include "CPInfo.hpp"
#include "MethodInfo.hpp"

struct Type {
    uint8_t tag;
    union {
        uint32_t type_empty;
        uint32_t type_boolean;
        uint32_t type_byte;
        uint32_t type_char;
        uint32_t type_short;
        uint32_t type_int;
        uint32_t type_float;
        uint64_t type_reference;
        uint32_t type_returnAddress;
        uint64_t type_long;
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
