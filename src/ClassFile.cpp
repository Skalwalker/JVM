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
    for (int cp = 0; cp <= 27; cp++) {
        uint8_t tag = ClassFileReader<uint8_t>().readBytes(fp);
        cout << hex << tag << endl;
        CPInfo cpInfo(tag, fp);
        constantPool.push_back(cpInfo);
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
