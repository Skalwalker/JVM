#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "ClassFile.hpp"
#include <iostream>

class Printer {
private:
    ClassFile cls_file;
    void printGeneralInfo();
    void printHeader(string sectionName);
    void printFooter(string sectionName);
public:
    Printer(ClassFile *classFile);
    void manualHelloWorld(ClassFile classFile);
};

#endif
