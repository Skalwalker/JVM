#ifndef __PRINTER_H__
#define __PRINTER_H__

#define s(x) string(x)

#include "./models/ClassFile.hpp"
#include "./runtime/InstructionsManager.hpp"
#include <iostream>
#include <iomanip>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

class Printer {
private:
    ClassFile cls_file;
    InstructionsManager* instructionsManager;
    vector<CPInfo> cp_vec;
    void printGeneralInfo();
    void printConstantPool();
    void printInterfaces();
    void printFields();
    void printMethods();
    void printAttributes(bool inside_type, std::vector<AttributeInfo> vec, string starter);
    string setAccessFlagsNames(uint16_t access_flags);
    string printCPString(CPInfo cp);
    string majorVersionValue(uint16_t version);
    string flagDescription(uint16_t flag);
    void printHeader(string sectionName);
    string printCPString(uint16_t cp_num);
    void printCPBody(CPInfo cp);
    void printAttributesBody(AttributeInfo atr, string starter);
    void getValue(Instruction instr, AttributeInfo atr, int i, int *jump, string starter);
public:
    Printer(ClassFile classFile, InstructionsManager* instructionsManager);
};

#endif
