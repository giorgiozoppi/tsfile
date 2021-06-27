/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
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
#ifndef IOTDB__BCONV__H
#define IOTDB__BCONV__H

#include <string>

#include <iotdb.h>
#include <util/buffer_window.h>

namespace iotdb { namespace bconv {

template<typename Tp>
Tp to(const util::buffer_window& bytes) {
    Tp v = 0ULL;
    if (iotdb::byte_order == bytes.order()) {
        std::copy(bytes.begin(), bytes.end(),
                  (util::buffer_window::value_type*) &v);
    } else {
        std::copy(bytes.rbegin(), bytes.rend(),
                  (util::buffer_window::value_type*) &v);
    }
    return v;
}

template<>
bool to(const util::buffer_window& bytes) {
    uint64_t x = static_cast<uint64_t>(bytes[0]);
    return 1ULL == x;
}

template<>
std::string to(const util::buffer_window& bytes) {
    return std::string(bytes.begin(), bytes.end());
}
} }

#endif // IOTDB__BCONV__H
