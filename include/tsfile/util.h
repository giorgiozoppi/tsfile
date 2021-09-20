#ifndef IOTDB_NATIVE_UTIL_HASHER_H
#define IOTDB_NATIVE_UTIL_HASHER_H
#include <vector>
namespace iotdb::util {

// extend with concepts.
template <typename T>
inline bool hashed_remove(std::vector<T>& container, const T& value) {
    auto hash_value = value.hash_code();
    auto res = std::remove_if(std::begin(container), std::end(container),
                              [=](auto current) { return current.hash_code() == hash_value; });
    return res != container.end();
}
}  // namespace iotdb::util
#endif