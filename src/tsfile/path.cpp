#include <string>
#include "tsfile/io/path.h"

namespace iotdb::tsfile::io {
using iotdb::tsfile
    : path::path(const std::string& device, const iotdb::tsfile::measurement& measure) _device(device), _measurement(measure) {}

uint64_t path::hash_code() const { return _hash_code; }
std::filesystem::path path::fullpath() const {}
std::string device() const { return _device; }
std::string path::measurement() const { return _measurement; }
void path::set_measurement(const std::string& measure) { _measurement = measure; }
}  // namespace iotdb::tsfile::io
