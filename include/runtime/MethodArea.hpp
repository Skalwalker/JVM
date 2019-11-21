#ifndef METHOD_AREA_H_INCLUDED
#define METHOD_AREA_H_INCLUDED

#include <vector>
#include <map>
#include "../models/ClassFile.hpp"

using namespace std;

class MethodArea {
private:
    map<string, ClassFile> classes;
public:
    ClassFile getClassFile(string);
    void insertClass(ClassFile);
};

#endif
