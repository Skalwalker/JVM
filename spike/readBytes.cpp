#include <fstream>
#include <cstdint>
#include <iostream>

using namespace std;

template<typename T>
T lendianToBigendian(T val) {}

template <>
uint16_t littleEndianToBigendian<uint16_t>(uint16_t val) {
    return (val << 8) | (val >> 8);
}

template <>
uint32_t littleEndianToBigendian<uint32_t>(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}

template<typename T>
static T readBytes(FILE * fp) {
    int bytes_for_read = sizeof(T);
    T p;
    fread(&p, bytes_for_read, 1, fp);
    p = lendianToBigendian(p);
    return (p);
}

int main() {
    uint32_t magicNumber;
    FILE * fp;

    fp = fopen("../examples/HelloWorld.class", "rb");
    magicNumber = readBytes<__typeof__(magicNumber)>(fp);
    cout << magicNumber << endl;
    cout << hex << "0x" << magicNumber << endl;

    return 0;
}
