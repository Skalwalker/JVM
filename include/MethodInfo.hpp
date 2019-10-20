#include <cstdint>
#include <fstream>
#include <iostream>
#include "ClassFileReader.hpp"

// #define ACC_PUBLIC 0x0001
// #define ACC_PRIVATE 0x0002
// #define ACC_PROTECTED 0x0004
// #define ACC_STATIC 0x0008
// #define ACC_FINAL 0x0010
// #define ACC_BRIDGE 0x0040
// #define ACC_VARARGS 0x0080
// #define ACC_NATIVE 0x0100
// #define ACC_ABSTRACT 0x0400
// #define ACC_STRICT 0x0800
// #define ACC_SYNTHETIC 0x1000


class MethodInfo {
  private:
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    // std::vector<AttributeInfo> attributes;
  public:
    MethodInfo(FILE * fp);
};
