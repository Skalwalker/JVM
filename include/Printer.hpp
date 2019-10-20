#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "ClassFile.hpp"
#include <iostream>

class Printer {
private:
    ClassFile cls_file;
    void printGeneralInfo();
    void printConstantPool();
    void printInterfaces();
    void printHeader(string sectionName);
    void printFooter(string sectionName);
    void printCPBody(CPInfo cp);
public:
    Printer(ClassFile classFile);
};

#endif
