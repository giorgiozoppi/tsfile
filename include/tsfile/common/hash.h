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
#include <tsfile/common/common.h>

// @todo use static/dynamic polymorphism and an generate an hash function that get an
// Hashable objet
#include <optional>
#if 0
namespace iotdb::tsfile::common {
struct SipHash {};
struct MurmurHash3 {};
template <typename KeyType, typename AlgorithmKind>
std::optional<ByteBuffer> Hash(const KeyType& key) {
    return std::nullopt;
}
template <>
std::optional<ByteBuffer> Hash<ByteBuffer, MurmurHash3>(const ByteBuffer& key) {
    return std::nullopt;
}
template <>
std::optional<ByteBuffer> Hash<ByteBuffer, SipHash>(const ByteBuffer& key) {
    return std::nullopt;
}
}  // namespace iotdb::tsfile::common
class Hasher {
   public:
    template <typename T>
    void Add(T data);
    uint64_t Compute();

   private:
    void AddData(uint64_t data, std::vector<uint8_t>& value);
    uint64_t GenerateKeyPart();
    std::vector<uint8_t> _data;
};

#endif
#endif
