#ifndef __FIELDINFO_H__
#define __FIELDINFO_H__
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include "ClassFileReader.hpp"
#include "AttributeInfo.hpp"
#include "CPInfo.hpp"

// #define ACC_PUBLIC 0x0001
// #define ACC_PRIVATE 0x0002
// #define ACC_PROTECTED 0x0004
// #define ACC_STATIC 0x0008
// #define ACC_FINAL 0x0010
// #define ACC_VOLATILE 0x0040
// #define ACC_TRANSIENT 0x0080
// #define ACC_SYNTHETIC 0x1000
// #define ACC_ENUM 0x4000


class FieldInfo {
  public:
    FieldInfo(vector<CPInfo> cp, FILE * fp);
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    vector<AttributeInfo> attributes;

    void setAttributes(vector<CPInfo> cp, FILE * fp);
};

#endif
