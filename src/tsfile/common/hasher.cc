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

#if 0

#include "tsfile/common/hasher.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <numeric>
#include <random>
#include <utility>

#include "tsfile/common/siphash.h"

namespace iotdb::tsfile {

typedef union {
    uint8_t array[8];
    uint64_t data;
} bitarray_t;

void hasher::add_data(uint64_t data, std::vector<uint8_t>& value) {
    bitarray_t ba;
    ba.data = data;
    for (auto b : ba.array) {
        value.emplace_back(b);
    }
}
void hasher::add(std::byte data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current, _data);
}
void hasher::add(double data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(current));
    add_data(current, _data);
}
void hasher::add(float data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current, _data);
}
void hasher::add(long data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current, _data);
}
void hasher::add(int data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current, _data);
}
void hasher::add(unsigned int data) {
    uint64_t current;
    auto siz = sizeof(data) > sizeof(current) ? sizeof(current) : sizeof(data);
    memcpy(&current, &data, siz);
    add_data(current, _data);
}
void hasher::add(unsigned long data) {
    uint64_t current;
    auto siz = sizeof(data) > sizeof(current) ? sizeof(current) : sizeof(data);
    memcpy(&current, &data, siz);
    add_data(current, _data);
}
uint64_t hasher::gen_key_part() {
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<uint64_t> dis(1, std::numeric_limits<uint64_t>::max());
    uint64_t part = dis(mt);
    return part;
}
uint64_t hasher::compute() {
    std::vector<uint8_t> key;
    bitarray_t output;
    for (size_t i = 0; i < 2; ++i) {
        add_data(gen_key_part(), key);
    }
    // SipHash computes a 64-bit message authentication code from a variable-length message and
    // 128-bit secret key.
    siphash(_data.data(), _data.size(), key.data(), output.array, 8);
    return output.data;
}
}  // namespace iotdb::tsfile
#endif
