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
    string majorVersionValue(uint16_t version);
    string flagDescription(uint16_t flag);
    void printHeader(string sectionName);
    void printFooter(string sectionName);
    void printCPBody(CPInfo cp);
public:
    Printer(ClassFile classFile);
};

#endif
