#include "../include/ClassFileReader.hpp"

template <>
uint16_t ClassFileReader<uint16_t>::littleEndianToBigEndian(uint16_t val) {
    return (val << 8) | (val >> 8);
}

template <>
uint32_t ClassFileReader<uint32_t>::littleEndianToBigEndian(uint32_t val) {
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
    return (val << 16) | (val >> 16);
}
