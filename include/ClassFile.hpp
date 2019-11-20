#ifndef __CLASSFILE_H__
#define __CLASSFILE_H__

#include <cstdint>
#include <vector>
#include <fstream>
#include "CPInfo.hpp"
#include "AttributeInfo.hpp"
#include "FieldInfo.hpp"
#include "MethodInfo.hpp"
#include "ClassFileReader.hpp"

using namespace std;

#define typeof __typeof__

class ClassFile {
    private:
    uint32_t magicNumber;
    uint16_t minorVersion;
    uint16_t majorVersion;
    uint16_t constantPoolCount;
    vector<CPInfo> constantPool;
    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;
    uint16_t interfacesCount;
    vector<uint16_t> interfaces;
    uint16_t fieldsCount;
    vector<FieldInfo> fields;
    uint16_t methodsCount;
    vector<MethodInfo> methods;
    uint16_t attributesCount;
    vector<AttributeInfo> attributes;

    void setMagicNumber(FILE * fp);
    void setMajorVersion(FILE * fp);
    void setMinorVersion(FILE * fp);
    void setConstantPoolCount(FILE * fp);
    void setConstantPool(FILE * fp);
    void setAccessFlags(FILE * fp);
    void setThisClass(FILE * fp);
    void setSuperClass(FILE * fp);
    void setInterfacesCount(FILE * fp);
    void setInterfaces(FILE * fp);
    void setFieldsCount(FILE * fp);
    void setFields(FILE * fp);
    void setMethodsCount(FILE * fp);
    void setMethods(FILE * fp);
    void setAttributesCount(FILE * fp);
    void setAttributes(FILE * fp);
    public:
    ClassFile(FILE * fp);
    ClassFile();
    static const uint32_t MAGIC_NUMBER = 0xCAFEBABE;
    static const uint16_t ACC_PUBLIC = 0x0001;
    static const uint16_t ACC_FINAL = 0x0010;
    static const uint16_t ACC_SUPER = 0x0020;
    static const uint16_t ACC_INTERFACE = 0x0200;
    static const uint16_t ACC_ABSTRACT = 0x0400;
    static const uint16_t ACC_SYNTHETIC = 0x1000;
    static const uint16_t ACC_ANNOTATION = 0x2000;
    static const uint16_t ACC_ENUM = 0x4000;

    uint32_t getMagicNumber();
    uint16_t getMajorVersion();
    uint16_t getMinorVersion();
    uint16_t getConstantPoolCount();
    vector<CPInfo> getConstantPool();
    uint16_t getAccessFlags();
    uint16_t getThisClass();
    uint16_t getSuperClass();
    uint16_t getInterfacesCount();
    vector<uint16_t> getInterfaces();
    uint16_t getFieldsCount();
    vector<FieldInfo> getFields();
    uint16_t getMethodsCount();
    vector<MethodInfo> getMethods();
    uint16_t getAttributesCount();
    vector<AttributeInfo> getAttributes();
};

#endif
