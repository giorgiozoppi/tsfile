#ifndef IOTDB_NATIVE_ALGORITHMS_H
#define IOTDB_NATIVE_ALGORITHMS_H
#include <tsfile/common/concepts.h>

#include <algorithm>
#include <vector>

namespace tsfile {
template <typename Hashable>
inline bool RemoveUsingHash(std::vector<Hashable>& container, const Hashable& value) {
    auto hash_value = value.HashCode();
    auto res = std::remove_if(std::begin(container), std::end(container),
                              [=](auto current) { return current.HashCode() == hash_value; });
    return res != container.end();
}
}  // namespace tsfile
#endif
