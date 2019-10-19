#ifndef __CLASSFILEREADER_H__
#define __CLASSFILEREADER_H__
#include <fstream>

template<class T>

class ClassFileReader {
    private:
        T littleEndianToBigEndian(T val);
    public:
        T readBytes(FILE * fp);
};

template<class T>
T ClassFileReader<T>::readBytes(FILE * fp) {
    int bytesForRead = sizeof(T);
    T readBytes;
    fread(&readBytes, bytesForRead, 1, fp);
    readBytes = ClassFileReader<T>::littleEndianToBigEndian(readBytes);

    return (readBytes);
}

template<class T>
T ClassFileReader<T>::littleEndianToBigEndian(T val) {}

#endif
