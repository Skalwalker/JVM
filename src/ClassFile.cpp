#include <iostream>
#include "../include/ClassFile.hpp"
using namespace std;

// Constructor
ClassFile::ClassFile(FILE * fp) {
    this->setMagicNumber(fp);
    this->setMinorVersion(fp);
    this->setMajorVersion(fp);
    this->setConstantPoolCount(fp);
    this->setConstantPool(fp);
    this->setAccessFlags(fp);
    this->setThisClass(fp);
    this->setSuperClass(fp);
    this->setInterfacesCount(fp);
    this->setInterfaces(fp);
    this->setFieldsCount(fp);
    this->setFields(fp);
    this->setMethodsCount(fp);
    this->setMethods(fp);
    this->setAttributesCount(fp);
}

void ClassFile::setMagicNumber(FILE * fp) {
    ClassFileReader<typeof(magicNumber)> magic;
    magicNumber = magic.readBytes(fp);
}

void ClassFile::setMinorVersion(FILE * fp) {
    ClassFileReader<typeof(minorVersion)> minor;
    minorVersion = minor.readBytes(fp);
}

void ClassFile::setMajorVersion(FILE * fp) {
    ClassFileReader<typeof(majorVersion)> major;
    majorVersion = major.readBytes(fp);
}

void ClassFile::setConstantPoolCount(FILE * fp) {
    ClassFileReader<typeof(constantPoolCount)> cpCount;
    constantPoolCount = cpCount.readBytes(fp);
}

void ClassFile::setConstantPool(FILE * fp) {
    int cpCount = constantPoolCount;
    for (int cp = 0; cp < cpCount-1; cp++) {
        uint8_t tag = ClassFileReader<uint8_t>().readBytes(fp);
        CPInfo cpInfo(tag, fp);
        constantPool.push_back(cpInfo);
        if (tag == 5 || tag == 6){
          CPInfo cpInfo(0, fp);
          constantPool.push_back(cpInfo);
          cp++;
        }
    }
}

void ClassFile::setAccessFlags(FILE * fp) {
    ClassFileReader<typeof(accessFlags)> flags;
    accessFlags = flags.readBytes(fp);
}

void ClassFile::setThisClass(FILE * fp) {
    ClassFileReader<typeof(thisClass)> thisC;
    thisClass = thisC.readBytes(fp);
}

void ClassFile::setSuperClass(FILE * fp) {
    ClassFileReader<typeof(superClass)> superC;
    superClass = superC.readBytes(fp);
}

void ClassFile::setInterfacesCount(FILE * fp) {
    ClassFileReader<typeof(interfacesCount)> itCount;
    interfacesCount = itCount.readBytes(fp);
}

void ClassFile::setInterfaces(FILE * fp) {
    int iCount = interfacesCount;
    for (int i = 0; i < iCount; i++) {
        uint16_t interface = ClassFileReader<uint16_t>().readBytes(fp);
        interfaces.push_back(interface);
    }
}

void ClassFile::setFieldsCount(FILE * fp) {
    ClassFileReader<typeof(fieldsCount)> f_count;
    fieldsCount = f_count.readBytes(fp);
}

void ClassFile::setFields(FILE * fp) {
  int fCount = fieldsCount;
  for (int i = 0; i < fCount; i++) {
      FieldInfo fieldInfo(fp);
      fields.push_back(fieldInfo);
  }
}

void ClassFile::setMethodsCount(FILE * fp) {
    ClassFileReader<typeof(methodsCount)> m_count;
    methodsCount = m_count.readBytes(fp);
}

void ClassFile::setMethods(FILE * fp) {
  int mCount = methodsCount;
  for (int i = 0; i < mCount; i++) {
      MethodInfo methodInfo(fp);
      methods.push_back(methodInfo);
  }
}

void ClassFile::setAttributesCount(FILE * fp) {
    ClassFileReader<typeof(attributesCount)> a_count;
    attributesCount = a_count.readBytes(fp);
}

uint32_t ClassFile::getMagicNumber() {
    return magicNumber;
}

uint16_t ClassFile::getMinorVersion() {
    return minorVersion;
}

uint16_t ClassFile::getMajorVersion() {
    return majorVersion;
}

uint16_t ClassFile::getConstantPoolCount() {
    return constantPoolCount;
}

vector<CPInfo> ClassFile::getConstantPool() {
    return constantPool;
}

uint16_t ClassFile::getAccessFlags() {
    return accessFlags;
}

uint16_t ClassFile::getThisClass() {
    return thisClass;
}

uint16_t ClassFile::getSuperClass() {
    return superClass;
}

uint16_t ClassFile::getInterfacesCount() {
    return interfacesCount;
}

vector<uint16_t> ClassFile::getInterfaces() {
    return interfaces;
}

uint16_t ClassFile::getFieldsCount() {
    return fieldsCount;
}

vector<FieldInfo> ClassFile::getFields() {
    return fields;
}

uint16_t ClassFile::getMethodsCount() {
    return methodsCount;
}

vector<MethodInfo> ClassFile::getMethods() {
    return methods;
}

uint16_t ClassFile::getAttributesCount(){
    return attributesCount;
}
