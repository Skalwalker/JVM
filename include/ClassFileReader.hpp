#include <fstream>

template<class T>

class ClassFileReader {
    private:
        template <typename T> T ClassFileReader::littleEndianToBigEndian(T val) {}

        template <>
        uint16_t ClassFileReader::littleEndianToBigEndian<uint16_t>(uint16_t val) {
            return (val << 8) | (val >> 8);
        }

        template <>
        uint32_t ClassFileReader::littleEndianToBigEndian<uint32_t>(uint32_t val) {
            val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
            return (val << 16) | (val >> 16);
        }

    public:
        template<typename T>
        T ClassFileReader::readBytes(FILE * fp) {
            int bytesForRead = sizeof(T);
            T readBytes;
            fread(&readBytes, bytesForRead, 1, fp);
            readBytes = littleEndianToBigEndian(readBytes);
            return (readBytes);
        }
};
