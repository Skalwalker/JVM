#include "../../include/loader/ClassLoader.hpp"

ClassLoader::ClassLoader(string path) {
    this->classesPath = path;
}

ClassFile ClassLoader::loadClassFile(string className) {
    FILE * fp;

    if (className.compare("java/lang/Object") == 0) {
        fp = fopen("java/lang/Object.class", "rb");
    } else {
        fp = fopen((classesPath + "/" + className + ".class").c_str(), "rb");
    }

    if (fp != NULL) {
        ClassFile classFile(fp);
        methodArea->insertClass(classFile);
        fclose(fp);
        return classFile;
    }

    cout << "Algum erro na abertura do programa: " << classesPath+className << endl;
    exit(0);
}
