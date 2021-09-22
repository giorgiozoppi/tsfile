#ifndef IOTDB_NATIVE_CONCEPTS_H
#define IOTDB_NATIVE_CONCEPTS_H
#include <concepts>
#include <cstdint>

namespace iotdb::tsfile {
template <typename T>
concept Serializable = requires {
    std::declval<T>().members();
    std::declval<T>().names();
};
/*
template <typename T>
concept HexConvertible = requires(T a) {
    std::declval<T>().hex();
}

template <typename T>
concept Hashable = requires(T a) {
    {
        a } -> (std::convertible_to<double> 
            || std::convertible_to<int> 
            || std::convertible_to<std::byte>
            || std::convertible_to<float> ) 
            || std::convertible_to<unsigned int>
            || std::convertible_to<long> || std::convertible_to<std::string>);
}; */
}  // namespace iotdb::tsfile
#endif
