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
#include <<type_traits>
#include <cstdint>

namespace iotdb::tsfile::common { {

template <typename T, typename S>
struct is_string
{
  static const bool value = false;
};

template <class T, class Traits, class Alloc>
struct is_string<T, std::basic_string<T, Traits, Alloc>>
{
  static const bool value = true;
};

template <typename T> concept HashFunction = requires {
    std::decl
}
template <typename T>
concept Serializable = requires {
    std::declval<T>().members();
};
template <typename T>
concept HexConvertible = requires(T a) {
    std::declval<T>().hex();
};
template <typename T>
concept Hashable = requires(T a) {
    std::declval<T>().hash_code();
};
template <typename T>
concept StatLike = requires(T a) {
    std::declval<T>().count();
    std::declval<T>().start_time();
    std::declval<T>().min_value();
    std::declval<T>().max_value();
    std::declval<T>().first_value();
    std::declval<T>().last_value();
    std::declval<T>().sum_value();
    std::declval<T>().extreme();
};
template <typename T> concept PrimitiveType = std::is_integral<T>() || is_string<T>::value || std::floating_point<T>;

template <typename T>
concept StatLikeHashable = StatLike<T> && Hashable<T>;
}  // namespace iotdb::tsfile
#endif
