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
#ifndef IOTDB_NATIVE_HASH_H
#define IOTDB_NATIVE_HASH_H

#include <tsfile/common/bytebuffer.h>
#include <tsfile/common/concepts.h>
#include <tsfile/common/murmurhash3.h>
#include <tsfile/common/pack.h>
#include <tsfile/model/chunk.h>

#include <array>
#include <functional>
#include <limits>
#include <random>
#include <type_traits>

namespace std {
template <>
struct hash<tsfile::Chunk> {
    std::size_t operator()(tsfile::Chunk const& s) const noexcept { return s.GetHashCode(); }
};
}  // namespace std

namespace tsfile {

template <int N>
struct HashFunction {
    static int hash(ByteBuffer&& data) {
        uint64_t hash_value = MurmurHash3<ByteBuffer, uint64_t>{}(std::move(data), N);
        return abs(static_cast<int>(hash_value)) % N;
    }
};

template <Serializable T>
struct ObjectHasher {
    uint64_t operator()(Serializable T& value) {
        ByteBuffer buffer;
        HashFunction<
        std::apply(
            [&outbuffer](Serializable const&... tupleArgs) {
                size_t tsize = std::tuple_size(tupleArgs);
                for (size_t i = 0; i < tsize; i++) {
                    auto val = std::get<i>(tupleArgs);
                    outbuffer << val;
                }
            },
            value.Members());
    }
};
}  // namespace tsfile
#endif
