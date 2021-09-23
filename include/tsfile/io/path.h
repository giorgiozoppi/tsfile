#ifndef IOTDB_NATIVE_PATH_H
#define IOTDB_NATIVE_PATH_H
#include <filesystem>
#include <string>

namespace iotdb::tsfile::io {
class path {
   public:
    path(const std::string& device, const std::string& measure);
    uint64_t hash_code() const;
    //auto operator<=>(const path& source) const;
    std::filesystem::path fullpath() const;
    std::string measurement() const;
    void set_measurement(const std::string& path);
    std::string str() const;
    std::string device() const;
    void set_device(const std::string& device);
   private:
    uint64_t _hash_code;
    std::string _device;
    std::string _measurement;
    std::filesystem::path _fullpath;
};
}
#endif