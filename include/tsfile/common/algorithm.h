#ifndef IOTDB_NATIVE_ALGORITHMS_H
#define IOTDB_NATIVE_ALGORITHMS_H
#include <tsfile/common/concepts.h>

#include <algorithm>
#include <vector>

namespace tsfile {
template <typename Hashable>
inline bool HasErasedValue(std::vector<Hashable>& container, const Hashable& value) {
    if (container.size() == 0) {
        return false;
    }
    auto hash_value = value.GetHashCode();
    auto res = std::erase_if(
        container, [hash_value](auto current) { return current.GetHashCode() == hash_value; });
    return res;
}
}  // namespace tsfile
#endif
