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

#include <boost/preprocessor.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

namespace tsfile {
typedef uint8_t Byte;

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
class Expected {
   public:
    Expected(const T& result) {
        _value = std::nullopt;
        _error = result;
    }
    Expected(const T& result, const V& value) {
        _value = std::make_optional(value);
        _error = result;
    }
    Expected(const T& result, const std::optional<V>& value) {
        _value = value;
        _error = result;
    }
    Expected(const Expected& source) : _value(source._value), _error(source._error) {}
    Expected& operator=(const Expected& source) {
        if (this != &source) {
            _value = source._value;
            _error = source._error;
        }
        return *this;
    }
    Expected& operator=(Expected&& source) {
        if (this != &source) {
            _value = std::move(source._value);
            _error = std::move(source._error);
        }
        return *this;
    }
    Expected(Expected&& vr) {
        _value = std::move(vr._value);
        _error = std::move(vr._error);
    }
    ~Expected() = default;
    auto Value() const { return _value.value(); }
    bool HasValue() const { return _value.has_value(); }
    T Result() const { return _error; }

   private:
    template <typename K, typename Z>
    friend std::tuple<K, Z> to_tuple(const Expected<K, Z>& v);
    std::optional<V> _value{std::nullopt};
    T _error;
};

template <typename T>
using StatusResult = Expected<T, std::byte>;

#if defined(__GNUC__)
#define PP_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define PP_FUNCTION __FUNCSIG__
#else
#define PP_FUNCTION __func__
#endif

#define PP_QUOTE(x) #x
#define PP_STRINGIZE(x) PP_QUOTE(x)
#define PP_WHERE __FILE__ ":" PP_STRINGIZE(__LINE__)

#define EXPOSE_MEMBERS(...)                                       \
    auto Members() { return std::forward_as_tuple(__VA_ARGS__); } \
    auto Members() const { return std::forward_as_tuple(__VA_ARGS__); }

///
/// @brief Function used to extract a value and use in stuctured binding.
/// @param v value result to convert in a tuple.
///
template <typename K, typename Z>
std::tuple<K, Z> to_tuple(const Expected<K, Z>& v) {
    return {v._error, v._value.value()};
}
/// @brief Defines an error when looking an item in a BitMap.

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
