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
#ifndef IOTDB__TSFILE__UTILS__BLOOM_FILTER__H
#define IOTDB__TSFILE__UTILS__BLOOM_FILTER__H

#include <unordered_map>

#include <tsfile/file/metadata/device_metadata_index.h>
#include <util/bitset.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb { namespace tsfile { namespace utils {

class bloom_filter {
    class hash_function {
        int32_t _cap;
        int32_t _seed;

    public:
        hash_function(int32_t cap, int32_t seed): _cap{cap}, _seed{seed} {}

        int32_t hash(const char* /*str*/) { return 0; }
        // TODO: return Math.abs(Murmur128Hash.hash(value, seed)) % cap
    };

    using funcs_type = std::vector<hash_function>;

    static constexpr const int32_t MAXIMAL_HASH_FUNCTION_SIZE = 8;
    static constexpr const int32_t SEEDS[] = {5, 7, 11, 19, 31, 37, 43, 59};
    util::bitset bs;
    int32_t sz;
    funcs_type::size_type hfs;
    funcs_type fns;

public:
    explicit bloom_filter() {}

    explicit bloom_filter(util::bitset && bitset, int32_t function_size, int32_t hash_function_size)
        : bs{bitset}
        , sz{function_size}
        , hfs{std::max<funcs_type::size_type>(MAXIMAL_HASH_FUNCTION_SIZE, hash_function_size)}
    {
        for (funcs_type::size_type i = 0; i < hfs; i++) {
            fns.emplace_back(hash_function(sz, SEEDS[i]));
        }
    }
};

inline bloom_filter make_bloom_filter(util::buffer_window& buf) noexcept {
    util::buffer_window bytes = rwio::read<util::buffer_window>(buf).value();
    int32_t function_size = rwio::read<int32_t>(buf).value();
    int32_t hash_function_size = rwio::read<int32_t>(buf).value();
    return bloom_filter{util::make_bitset(bytes), function_size, hash_function_size};
}

}}}

#endif // IOTDB__TSFILE__UTILS__BLOOM_FILTER__H
