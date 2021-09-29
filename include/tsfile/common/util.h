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
#ifndef IOTDB_NATIVE_UTIL_HASHER_H
#define IOTDB_NATIVE_UTIL_HASHER_H
#include <vector>
namespace iotdb::tsfile::common {

// extend with concepts.
template <typename T>
inline bool remove_byhash(std::vector<T>& container, const T& value) {
    auto hash_value = value.hash_code();
    auto res = std::remove_if(std::begin(container), std::end(container),
                              [=](auto current) { return current.hash_code() == hash_value; });
    return res != container.end();
}
}  // namespace iotdb::util
#endif