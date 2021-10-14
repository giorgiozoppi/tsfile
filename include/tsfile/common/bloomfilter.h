/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IOTDB_COMMON_BLOOMFILTER
#define IOTDB_COMMON_BLOOMFILTER
#include <tsfile/common/bitmap.h>
#include <tsfile/common/common.h>
#include <tsfile/common/hash.h>

#include <array>
#include <bitset>
#include <cstddef>
#include <memory>

namespace tsfile {
// @todo
// Adapt from Cache Efficent Bloom filter implementation
template <typename HashFunction>
class GenericBloomFilter {
   public:
    static constexpr int kMinimalSize = 256;
    static constexpr int kMaximalHashFunctionSize = 8;
    static constexpr std::array<int, kMaximalHashFunctionSize> SEEDS = {5,  7,  11, 19,
                                                                        31, 37, 43, 59};
    GenericBloomFilter(const std::vector<Byte>& array, size_t hashFunctionSize) {
        for (auto& b : array) {
            _bits.Mark(b);
        }
        size_ = hashFunctionSize;
    }
    IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(GenericBloomFilter);

   private:
    BitMap _bits;
    std::vector<HashFunction> _function;
    size_t size_;
};
using BloomFilter = GenericBloomFilter<MurmurHash3<ByteBuffer, ByteBuffer>>;
}  // namespace tsfile
#endif