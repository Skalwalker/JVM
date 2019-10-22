#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "ClassFile.hpp"
#include <iostream>
#include <iomanip>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

class Printer {
private:
    ClassFile cls_file;
    vector<CPInfo> cp_vec;
    void printGeneralInfo();
    void printConstantPool();
    void printInterfaces();
    void printFields();
    void printMethods();
    void printAttributes(bool inside_type, std::vector<AttributeInfo> vec);
    string printCPString(CPInfo cp);
    string majorVersionValue(uint16_t version);
    string flagDescription(uint16_t flag);
    void printHeader(string sectionName);
    string printCPString(uint16_t cp_num);
    void printCPBody(CPInfo cp);
    void printAttributesBody(AttributeInfo atr, string starter);
public:
    Printer(ClassFile classFile);
};

#endif
