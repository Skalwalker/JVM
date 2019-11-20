#ifndef __CLASSLOADER_H_INCLUDED__
#define __CLASSLOADER_H_INCLUDED__

#include "ClassFile.hpp"
#include "MethodArea.hpp"

class ClassLoader {
public:
    MethodArea * methodArea;
    ClassLoader();
    ClassFile loadClassFile(ClassFile);
};

#endif
