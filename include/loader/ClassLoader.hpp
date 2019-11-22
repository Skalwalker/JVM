#ifndef __CLASSLOADER_H_INCLUDED__
#define __CLASSLOADER_H_INCLUDED__

#include "../models/ClassFile.hpp"
#include "../runtime/MethodArea.hpp"

class ClassLoader {
public:
    MethodArea * methodArea;
    ClassLoader();
    ClassFile loadClassFile(ClassFile);
};

#endif
