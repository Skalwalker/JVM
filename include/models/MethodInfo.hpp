#ifndef __METHODINFO_H__
#define __METHODINFO_H__
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "../loader/ClassFileReader.hpp"
#include "AttributeInfo.hpp"
#include "CPInfo.hpp"

using namespace std;

class MethodInfo {
private:
    void setAccessFlagsNames();
public:
    MethodInfo(vector<CPInfo> cp, FILE * fp);
    MethodInfo();
    string access_flags_names;
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    vector<AttributeInfo> attributes;

    static const uint16_t ACC_PUBLIC = 0x0001;
    static const uint16_t ACC_PRIVATE = 0x0002;
    static const uint16_t ACC_PROTECTED = 0x0004;
    static const uint16_t ACC_STATIC = 0x0008;
    static const uint16_t ACC_FINAL = 0x0010;
    static const uint16_t ACC_BRIDGE = 0x0040;
    static const uint16_t ACC_VARARGS = 0x0080;
    static const uint16_t ACC_NATIVE = 0x0100;
    static const uint16_t ACC_ABSTRACT = 0x0400;
    static const uint16_t ACC_STRICT = 0x0800;
    static const uint16_t ACC_SYNTHETIC = 0x1000;

    void setAttributes(vector<CPInfo> cp, FILE * fp);
};

#endif
