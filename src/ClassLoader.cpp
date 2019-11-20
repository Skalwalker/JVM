#include "../include/ClassLoader.hpp"

ClassLoader::ClassLoader() {}

ClassFile ClassLoader::loadClassFile(ClassFile classfile) {
    methodArea->insertClass(classfile);

    return classfile;
}
