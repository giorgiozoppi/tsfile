/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#ifndef IOTDB_NATIVE_CONCEPTS_H
#define IOTDB_NATIVE_CONCEPTS_H
#include <concepts>
#include <cstdint>
#include <string>

template <typename T>
concept Serializable = requires {
    std::declval<T>().Members();
};
template <typename T>
concept HexConvertible = requires(T a) {
    std::declval<T>().Hex();
};
template <typename T>
concept Hashable = requires(T a) {
    std::declval<T>().HashCode();
    std::declval<T>().ByteHash();
};
template <typename T>
concept TsObject = Serializable<T> && Hashable<T>;


template <typename T, typename S>
struct is_string {
    static const bool value = false;
};
template <class T, class Traits, class Alloc>
struct is_string<T, std::basic_string<T, Traits, Alloc>> {
    static const bool value = true;
};

template <Hashable>
bool operator==(const Hashable auto& lhs, const Hashable auto& rhs) {
    return lhs.HashCode() == rhs.HashCode();
}
template <Hashable>
bool operator<=(const Hashable auto& lhs, const Hashable auto& rhs) {
    return lhs.HashCode() <= rhs.HashCode();
}
template <Hashable>
bool operator>=(const Hashable auto& lhs, const Hashable auto& rhs) {
    return lhs.HashCode() >= rhs.HashCode();
}
template <Hashable>
bool operator>(const Hashable auto& lhs, const Hashable auto& rhs) {
    return lhs.HashCode() > rhs.HashCode();
}
template <Hashable>
bool operator<(const Hashable auto& lhs, const Hashable auto& rhs) {
    return lhs.HashCode() < rhs.HashCode();
}

#endif
