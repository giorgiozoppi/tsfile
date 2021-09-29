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
#include <string>
#include <string_view>

namespace iotdb::tsfile::common {
#if __cplusplus >= 202002L 
typedef std::byte byte;
#else
typedef unsigned char byte;
#endif
///
/// @brief Suffix/Extension of the TSFile
///
constexpr std::string_view TSFILE_SUFFIX = ".tsfile";
}  // namespace io::tsfile::common
#endif
