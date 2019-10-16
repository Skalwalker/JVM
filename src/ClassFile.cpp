#include "../include/ClassFile.hpp"

// Construtor
ClassFile::ClassFile(FILE * fp) {
    this->setMagicNumber(fp);
}

void ClassFile::setMagicNumber(FILE * fp) {
    magicNumber = ClassFileReader::readBytes<typeof(magicNumber)>(fp);
}
