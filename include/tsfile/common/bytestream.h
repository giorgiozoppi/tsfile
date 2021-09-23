#include <istream>

#include "bytebuffer.h"
namespace iotdb::io {
typedef std::basic_ifstream<std::byte> ifbstream;
typedef std::basic_ofstream<std::byte> ofbstream;
typedef std::basic_istream<std::byte> ibstream;
typedef std::basic_ostream<std::byte> obstream;
constexpr int DEFAULT_BYTES_READ = 4096;
}  // namespace iotdb::io
