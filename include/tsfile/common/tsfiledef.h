#ifndef IOTDB_NATIVE_TSFILEDEF_H
#define IOTDB_NATIVE_TSFILEDEF_H
#include <string>
namespace tsfile::common::constants {
constexpr std::string TSFILE_SUFFIX = ".tsfile";
constexpr std::string TSFILE_HOME = "TSFILE_HOME";
constexpr std::string PATH_ROOT = "root";
constexpr std::string TMP_SUFFIX = "tmp";
constexpr std::string PATH_SEPARATOR = ".";
constexpr std::string PATH_SEPARATER_NO_REGEX = "\\.";
constexpr std::string DOUBLE_QUOTE = '"';
constexpr std::byte TIME_COLUMN_MASK = static_cast<std::byte>(0x80);
constexpr std::byte VALUE_COLUMN_MASK = static_cast<std::byte>(0x80);

}  // namespace tsfile::common::constants
#endif
