#include "../include/ClassFile.hpp"
#include <iostream>

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
    for (int cp = 0; cp <= cpCount; cp++) {
        uint8_t tag = ClassFileReader<uint8_t>().readBytes(fp);
        CPInfo cpInfo(tag, fp);
        constantPool.push_back(cpInfo);
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
        cout << "INTEFFACE = " << interface << endl;
        interfaces.push_back(interface);
    }
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
