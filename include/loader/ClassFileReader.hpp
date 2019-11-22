#ifndef __CLASSFILEREADER_H__
#define __CLASSFILEREADER_H__
#include <fstream>
#include <iostream>

template<class T>

class ClassFileReader {
    private:
        T littleEndianToBigEndian(T val);
    public:
        T readBytes(FILE * fp);
        static void advanceBytes(int size, FILE * fp);
};

template<class T>
T ClassFileReader<T>::readBytes(FILE * fp) {
    int bytesForRead = sizeof(T);
    T readBytes;
    fread(&readBytes, bytesForRead, 1, fp);
    if (bytesForRead == 4) {
        readBytes = ((readBytes << 8) & 0xFF00FF00) | ((readBytes >> 8) & 0xFF00FF);
        readBytes = (readBytes << 16) | (readBytes >> 16);
    } else if (bytesForRead == 2) {
        readBytes = (readBytes << 8) | (readBytes >> 8);
    }
    // readBytes = ClassFileReader<T>::littleEndianToBigEndian(readBytes);
    return (readBytes);
}

template<class T>
T ClassFileReader<T>::littleEndianToBigEndian(T val) {
  return val;
};

#endif
