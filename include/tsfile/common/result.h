/*
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 * We license this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef IOTDB_NATIVE_RESULT_H
#define IOTDB_NATIVE_RESULT_H
#include <optional>
namespace iotdb::tsfile::common {
enum class file_error { OK = 0, FORBIDDEN = 1, NOT_EXISTENT, ERROR_WRITING };
template <typename T, typename V>
class value_result {
   public:
    result() {}
    std::optional<V> value() const { return _value; }
    T error() const { return _error; }

   private:
    V _value;
    T _error;
};
template <typename T>
class status_result {
   public:
    status_result() {}
    status_result(const T& error) : _error(error) {}
    std::optional<T> value() const { return _value; }

   private:
    T _error;
};
}  // namespace iotdb::tsfile
#endif
