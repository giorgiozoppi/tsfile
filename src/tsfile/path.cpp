#include "tsfile/io/path.h"

#include <string>

namespace iotdb::tsfile::io {
path::path(const std::string& device, const std::string& measure): _device(device), _measurement(measure) {}

uint64_t path::hash_code() const { return _hash_code; }
std::filesystem::path path::fullpath() const {
    return _fullpath;
}
std::string path::device() const { return _device; }

std::string path::str() const { return _fullpath.c_str();}
std::string path::measurement() const { return _measurement; }
void path::set_measurement(const std::string& measure) { _measurement = measure; }
}  // namespace iotdb::tsfile::io
