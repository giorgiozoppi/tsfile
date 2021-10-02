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
#include <tsfile/common/common.h>

#include <array>
#include <bitset>
#include <cstddef>
#include <memory>

namespace tsfile {
// @todo
// Adapt from Cache Efficent Bloom filter implementation
class BloomFilter {
   public:
    static constexpr int kMinimalSize = 256;
    static constexpr int kMaximalHashFunctionSize = 8;
    static constexpr std::array<int, kMaximalHashFunctionSize> SEEDS = {5,  7,  11, 19,
                                                                          31, 37, 43, 59};

};
}  // namespace iotdb::tsfile::common
#ifdef 0

class HashFunction {};
class BloomFilter {
    static constexpr int kMinimalSize = 256;
    static constexpr int kMaximalHashFunctionSize = 8;
    static constexpr std::array<int, kMaximalHashFunctionSize> SEEDS = {5,  7,  11, 19,
                                                                          31, 37, 43, 59};
    int size_;
    int hash_function_size_;
    bits;
    HashFunction[] func;

    // do not try to initialize the filter by construction method
   private:
    BloomFilter(std::byte[] bytes, int size, int hashFunctionSize) {
        this.size_ = size;
        this.hash_function_size_ = hashFunctionSize;
        func = new HashFunction[hashFunctionSize];
        for (int i = 0; i < hashFunctionSize; i++) {
            func[i] = new HashFunction(size, SEEDS[i]);
        }

        bits = BitSet.valueOf(bytes);
    }
    BloomFilter(int size, int hashFunctionSize) {
        this.size = size;
        this.hashFunctionSize = hashFunctionSize;
        func = new HashFunction[hashFunctionSize];
        for (int i = 0; i < hashFunctionSize; i++) {
            func[i] = new HashFunction(size, SEEDS[i]);
        }

        bits = new BitSet(size);
    }
};
#endif

#endif