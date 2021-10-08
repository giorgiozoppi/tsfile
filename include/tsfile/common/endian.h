#ifndef ENDIAN_H
#define ENDIAN_H
#include <cstdlib>
#include <cstdint>
/// Endianess
namespace {
// here we handle endianess.
enum class Endianess { LittleEndian = 0, BigEndian };

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || defined(__BIG_ENDIAN__) ||         \
    defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || defined(_MIBSEB) || \
    defined(__MIBSEB) || defined(__MIBSEB__)
#define IOTDB_BIG_ENDIAN 1

constexpr Endianess ByteOrder = Endianess::BigEndian;
constexpr uint16_t to_big_endian(uint16_t n) { return n; }
constexpr uint32_t to_big_endian(uint32_t n) { return n; }
constexpr uint64_t to_big_endian(uint64_t n) { return n; }

#else
#define IOTDB_BIG_ENDIAN 0
constexpr Endianess ByteOrder = Endianess::LittleEndian;
constexpr uint16_t to_big_endian(uint16_t x) {
    return ((uint16_t)((((x) >> 8) & 0xff) | (((x)&0xff) << 8)));
}
constexpr uint32_t to_big_endian(uint32_t x) {
    return ((((x)&0xff000000u) >> 24) | (((x)&0x00ff0000u) >> 8) | (((x)&0x0000ff00u) << 8) |
            (((x)&0x000000ffu) << 24));
}
constexpr uint64_t to_big_endian(uint64_t x) {
    return ((((x)&0xff00000000000000ull) >> 56) | (((x)&0x00ff000000000000ull) >> 40) |
            (((x)&0x0000ff0000000000ull) >> 24) | (((x)&0x000000ff00000000ull) >> 8) |
            (((x)&0x00000000ff000000ull) << 8) | (((x)&0x0000000000ff0000ull) << 24) |
            (((x)&0x000000000000ff00ull) << 40) | (((x)&0x00000000000000ffull) << 56));
}
short to_big_endian(short s, Endianess order) {
    unsigned char c1, c2;

    if (order == Endianess::BigEndian) {
        return s;
    }
    c1 = s & 255;
    c2 = (s >> 8) & 255;
    return (c1 << 8) + c2;
}
int to_big_endian(int value, Endianess order) {
    if (order == Endianess::BigEndian) {
        return value;
    }
    unsigned char c1, c2;

    c1 = value & 255;
    c2 = (value >> 8) & 255;

    return (c1 << 8) + c2;
}
double to_big_endian(double value, Endianess order) {
    if (order == Endianess::BigEndian) {
        return value;
    }
    unsigned char bytes[8];
    unsigned char tmp[8];
    double ret;
    // if there is a better way than using old style c, welcome!
    std::memcpy(bytes, &value, sizeof(bytes));
    for (size_t i = 0; i < 8; i++) {
        tmp[8 - (i + 1)] = bytes[i];
    }
    std::memcpy(&ret, tmp, 8);
    return ret;
}
float to_big_endian(float value, Endianess order) {
    if (order == Endianess::BigEndian) {
        return value;
    }
    // it's ugly
    uint32_t tmp = static_cast<uint32_t>(value);
    tmp = to_big_endian(tmp);
    return static_cast<float>(tmp);
}

template <typename T>
T endian_aware(T r)  // template funzione
{
    if (sizeof(T) == 1) {
        return r;
    }
    return to_big_endian(r, ByteOrder);
}

#endif
}  // namespace
#endif  //
