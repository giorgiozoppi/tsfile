#ifndef IOTDB_NATIVE_COMMON_H
#define IOTDB_NATIVE_COMMON_H

#ifndef IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN
#define IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;                 \
    void operator=(const TypeName&) = delete
#endif

#ifndef IOTDB_NATIVE_DEFAULT_MOVE_AND_ASSIGN
#define IOTDB_NATIVE_DEFAULT_MOVE_AND_ASSIGN(TypeName) \
    TypeName(TypeName&&) = default;                    \
    TypeName& operator=(TypeName&&) = default
#endif

// include file zone.

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace tsfile {
typedef uint8_t Byte;
/// Endianess

// here we handle endianess.
// note that in java we've signed bytes as default.
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
// @todo
constexpr Endianess ByteOrder = Endianess::LittleEndian;

constexpr uint16_t to_big_endian(uint16_t x) {
    return ((__uint16_t)((((x) >> 8) & 0xff) | (((x)&0xff) << 8)));
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

#endif

///
/// @brief Suffix/Extension of the TSFile
///

constexpr std::string_view kTsFileSuffix = ".tsfile";

template <typename T>
constexpr bool IsOk(T t) {
    return t == T::OK;
}

///
/// @brief ValueResult class that combines return value and errors
///
/// Example a write that returns the written record:
/// using iotdb::tsfile::factory::make_record;
/// FileWriter writer("/tmp/datafile.tsfile");
/// auto record = MakeRecord(1632915425, "Temperature01");
/// record.AddPoint(std::move(MakeDataPoint<int>("CelciusDegree",10));
/// record.AddPoint(std::move(MakeDataPoint<int>("CelciusDegree",20));
/// auto [error, value] = get(file.Write(std::move(record)));
/// if IsOk(error) {
///  return ComputeAlgorithm(value);
/// }
///
template <typename T, typename V>
class ValueResult {
   public:
    ValueResult(const T& result, const V& value) {
        _value = std::make_optional(value);
        _error = result;
    }
    auto Value() const { return _value; }
    T Result() const { return _error; }
    ValueResult(ValueResult&& vr) {
        _value = std::move(vr._value);
        _error = std::move(vr._error);
    }

   private:
    template <typename K, typename Z>
    friend std::tuple<K, Z> get(const ValueResult<K, Z>& v);
    std::optional<V> _value{std::nullopt};
    T _error;
};
///
/// @brief StatusResult return  a result.
///
template <typename T>
class StatusResult {
   public:
    StatusResult(const T& result) { _error = result; }
    auto Result() const { return _error; }

   private:
    T _error;
};
///
/// @brief Function used to extract a value and use in stuctured binding.
/// @param v value result to convert in a tuple.
///
template <typename K, typename Z>
std::tuple<K, Z> get(const ValueResult<K, Z>& v) {
    return {v._error, v._value.value()};
}
enum class BitError { OK = 0, OUT_RANGE = 1 };

/// TsFile Markers
constexpr Byte kChunkGroupFooter = Byte{0};
constexpr Byte kChunkHeader = Byte{1};
constexpr Byte kSeparator = Byte{2};
constexpr Byte kVersion = Byte{3};
constexpr Byte kOperationIndexRange = Byte{4};
constexpr Byte kOnlyOnePageChunkHeader = Byte{5};

}  // namespace tsfile
#endif
