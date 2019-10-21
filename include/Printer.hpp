#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "ClassFile.hpp"
#include <iostream>
#include  <iomanip>

class Printer {
private:
    ClassFile cls_file;
    void printGeneralInfo();
    void printConstantPool();
    void printInterfaces();
    void printFields();
    void printMethods();
    void printAttributes(bool inside_type, std::vector<AttributeInfo> vec);
    string majorVersionValue(uint16_t version);
    string flagDescription(uint16_t flag);
    void printHeader(string sectionName);
    void printFooter(string sectionName);
    string printCPString(uint16_t cp_num);
    void printCPBody(CPInfo cp);
public:
    Printer(ClassFile classFile);
};

#endif
