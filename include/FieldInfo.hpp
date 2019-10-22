#ifndef __FIELDINFO_H__
#define __FIELDINFO_H__
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include "ClassFileReader.hpp"
#include "AttributeInfo.hpp"
#include "CPInfo.hpp"

class FieldInfo {
private:
    void setAccessFlagsNames();
public:
    FieldInfo(vector<CPInfo> cp, FILE * fp);
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
    static const uint16_t ACC_VOLATILE = 0x0040;
    static const uint16_t ACC_TRANSIENT = 0x0080;
    static const uint16_t ACC_SYNTHETIC = 0x1000;
    static const uint16_t ACC_ENUM = 0x4000;

    void setAttributes(vector<CPInfo> cp, FILE * fp);
};

#endif
