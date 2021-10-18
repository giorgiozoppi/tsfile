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
/*
A Bloom filter for representing a set S = {x1, x2,...,xn} of n elements is described by an array
of m bits, initially all set to 0. A Bloom filter uses k independent hash functions
h1,...,hk with range {1,...,m}. 
*/
template <typename HashFunction, int Size>
class GenericBloomFilter {
   public:
    static constexpr int kMinimalSize = 256;
    static constexpr int kMaximalHashFunctionSize = 8;
    static constexpr std::array<int, kMaximalHashFunctionSize> kSeeds = {5,  7,  11, 19,
                                                                         31, 37, 43, 59};
    GenericBloomFilter(size_t hash_function_size) {
        hash_size_ = hash_function_size;
        for (size_t i = 0; i < hash_size_; i++) {
            _function.emplace_back(std::move(HashFunction(Size, kSeeds[i])));
        }
        bits_ = std::bitset<Size>;
    }
    void Add(const std::string& value) {
        for (const auto& f : _function) {
            bits_.set(f.hash(value), true);
        }
    }
    bool Contains(const std::string& value) {
        if (value.size() == 0) {
          return false;
        }
        bool ret{false};
        size_t index{0};
        while(ret && index < hash_size_) {
          ret = bits_.test(_function.at(index++).hash(value));
        }
    } 
    
    size_t GetBitCount() const {
        size_t res = 0;
        for (size_t i = 0; i < Size; i++) {
            res += _bits.test(i) ? 1 : 0;
        }

        return res;
    }
    std::string ToString() const { return bits_.to_string(); }

    IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(GenericBloomFilter);

   private:
    std::bitset<Size> _bits;
    std::vector<HashFunction> _function;
    size_t hash_size_;
};
template <typename Size> using BloomFilter = GenericBloomFilter<MurmurHash3<ByteBuffer, uint64_t>, size_t Size>;  

}  // namespace tsfile

#endif