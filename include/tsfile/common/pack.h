#ifndef PACK_H
#define PACK_H
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
/// Endianess
namespace tsfile {
// here we handle endianess.
enum class Endianess { LittleEndian = 0, BigEndian };

typedef union byte4 {
    uint8_t byte[4];
    int ivalue;
    float fvalue;
    long lvalue;
} pack_byte4;
typedef union byte2 {
    uint8_t byte[2];
    short svalue;
} pack_byte2;
typedef union byte8 {
    uint8_t byte[8];
    double dvalue;
    long long lvalue;
    unsigned long long llvalue;
} pack_byte8;

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
#endif
class PackException : public std::logic_error {
   public:
    explicit PackException(const std::string& message, size_t args, size_t required_args)
        : std::logic_error::logic_error(message),
          packed_args_(args),
          required_args_(required_args) {
        std::ostringstream out;
        out << std::logic_error::what();
        out << " arguments ";
        out << std::to_string(packed_args_);
        out << " required ";
        out << std::to_string(required_args_);
        current_msg_ = out.str();
    }

    ~PackException() {}
    const char* what() const noexcept override { return current_msg_.c_str(); }

   private:
    size_t packed_args_;
    size_t required_args_;
    std::string current_msg_;
};

template <typename... Args>
short PackShort(const std::tuple<Args...>& t, Endianess order) {
    size_t n = sizeof...(Args);
    if (n != 2) {
        throw PackException("exception during packing", n, 2);
    }
    pack_byte2 v;
    int num{0};
    std::apply(
        [&num, &v, order](const auto&... args) {
            if (order != Endianess::BigEndian) {
                ((v.byte[1 - num++] = args), ...);
            } else {
                ((v.byte[num++] = args), ...);
            }
        },
        t);
    return v.svalue;
}
template <typename... Args>
int PackInt(const std::tuple<Args...>& t, Endianess order) {
    size_t n = sizeof...(Args);
    if (n != 4) {
        throw PackException("exception during packing", n, 4);
    }
    pack_byte4 v;
    int num{0};
    std::apply(
        [&num, &v, order](const auto&... args) {
            if (order != Endianess::BigEndian) {
                ((v.byte[3 - num++] = args), ...);
            } else {
                ((v.byte[num++] = args), ...);
            }
        },
        t);
    return v.ivalue;
}
template <typename... Args>
float PackFloat(const std::tuple<Args...>& t, Endianess order) {
    size_t n = sizeof...(Args);
    if (n != 4) {
        throw PackException("exception during packing", n, 4);
    }
    pack_byte4 v;
    int num{0};
    std::apply(
        [&num, &v, order](const auto&... args) {
            if (order != Endianess::BigEndian) {
                ((v.byte[3 - num++] = args), ...);
            } else {
                ((v.byte[num++] = args), ...);
            }
        },
        t);
    return v.fvalue;
}
template <typename... Args>
double PackDouble(const std::tuple<Args...>& t, Endianess order) {
    size_t n = sizeof...(Args);
    if (n != 8) {
        throw PackException("exception during packing", n, 4);
    }
    pack_byte8 v;
    int num{0};
    std::apply(
        [&num, &v, order](const auto&... args) {
            if (order != Endianess::BigEndian) {
                ((v.byte[7 - num++] = args), ...);
            } else {
                ((v.byte[num++] = args), ...);
            }
        },
        t);
    return v.dvalue;
}
template <typename... Args>
unsigned long long PackUnsignedLongLong(const std::tuple<Args...>& t, Endianess order) {
    size_t n = sizeof...(Args);
    if (n != 8) {
        throw PackException("exception during packing", n, 4);
    }
    pack_byte8 v;
    int num{0};
    std::apply(
        [&num, &v, order](const auto&... args) {
            if (order != Endianess::BigEndian) {
                ((v.byte[7 - num++] = args), ...);
            } else {
                ((v.byte[num++] = args), ...);
            }
        },
        t);
    return v.llvalue;
}

template <typename T>
inline std::vector<uint8_t> Unpack([[maybe_unused]] T value) {
    std::vector<uint8_t> data;
    return data;
}

template <typename T>
inline pack_byte2 EndianBytes2(T value) {
    pack_byte2 v, out;
    v.svalue = value;
    out.svalue = value;
    if (ByteOrder != Endianess::BigEndian) {
        out.byte[0] = v.byte[1];
        out.byte[1] = v.byte[0];
    }
    return out;
}
template <typename T>
inline pack_byte4 EndianBytes4(T value) {
    pack_byte4 v, out;
    if (std::is_same<T, float>::value) {
        v.fvalue = value;
        out.fvalue = value;
    } else {
        v.ivalue = value;
        out.fvalue = value;
    }
    if (ByteOrder != Endianess::BigEndian) {
        out.byte[0] = v.byte[3];
        out.byte[1] = v.byte[2];
        out.byte[2] = v.byte[1];
        out.byte[3] = v.byte[0];
    }

    return out;
}
inline pack_byte8 EndianBytes8(double value) {
    pack_byte8 v, out;
    v.dvalue = value;
    out.dvalue = value;
    if (ByteOrder != Endianess::BigEndian) {
        out.byte[0] = v.byte[7];
        out.byte[1] = v.byte[6];
        out.byte[2] = v.byte[5];
        out.byte[3] = v.byte[4];
        out.byte[4] = v.byte[3];
        out.byte[5] = v.byte[2];
        out.byte[6] = v.byte[1];
        out.byte[7] = v.byte[0];
    }
    return out;
}

template <>
inline std::vector<uint8_t> Unpack(short value) {
    std::vector<uint8_t> data;
    pack_byte2 v = EndianBytes2(value);
    for (int i = 0; i < 2; i++) {
        data.emplace_back(v.byte[i]);
    }
    return data;
}
template <>
inline std::vector<uint8_t> Unpack(unsigned short value) {
    std::vector<uint8_t> data;
    pack_byte2 v = EndianBytes2(value);
    for (int i = 0; i < 2; i++) {
        data.emplace_back(v.byte[i]);
    }
    return data;
}
template <>
inline std::vector<uint8_t> Unpack(float value) {
    std::vector<uint8_t> data;
    pack_byte4 v = EndianBytes4(value);
    for (int i = 0; i < 4; i++) {
        data.emplace_back(v.byte[i]);
    }
    return data;
}
template <>
inline std::vector<uint8_t> Unpack(int value) {
    std::vector<uint8_t> data;
    pack_byte4 v = EndianBytes4(value);
    for (int i = 0; i < 4; i++) {
        data.emplace_back(v.byte[i]);
    }
    return data;
}
template <>
inline std::vector<uint8_t> Unpack(unsigned int value) {
    std::vector<uint8_t> data;
    pack_byte4 v = EndianBytes4(value);
    for (int i = 0; i < 4; i++) {
        data.emplace_back(v.byte[i]);
    }
    return data;
}
template <>
inline std::vector<uint8_t> Unpack(double value) {
    std::vector<uint8_t> data;
    pack_byte8 v = EndianBytes8(value);
    for (int i = 0; i < 8; i++) {
        data.emplace_back(v.byte[i]);
    }
    return data;
}

}  // namespace tsfile

#endif