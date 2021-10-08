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
#include <tsfile/common/siphash.h>
#include <tsfile/common/concepts.h>
#include <tsfile/common/bytebuffer.h>

#include <array>
#include <limits>
#include <random>
#include <type_traits>


// @todo use static/dynamic polymorphism and an generate an hash function that get an
// Hashable objet
namespace tsfile {
    template <typename Key, typename RetValue>
struct MurmurHash3 {
    RetValue operator()(Key const& s) const noexcept {
        RetValue v;
        return v;
    }
};
template <>
struct MurmurHash3<ByteBuffer, ByteBuffer> {
    ByteBuffer operator()(ByteBuffer const& s) {
        ByteBuffer out(16);
        ByteBuffer key(s);
        std::random_device rd;
        std::mt19937 e{rd()};
        std::uniform_int_distribution<unsigned int> dist{0, 10000};
        auto seed = dist(e);
        MurmurHash3_x86_128(key.Data(), key.Size(), seed, out.Data());
        return out;
    }
};
struct SipHash {
    ByteBuffer operator()(ByteBuffer const& s) {
        ByteBuffer out(8);
        ByteBuffer local(s);
        std::random_device rd;
        std::mt19937 e{rd()};
        std::uniform_int_distribution<int> dist{0, 255};
        ByteBuffer key;
        for (size_t k = 0; k < 4; k++) {
            key.Append(dist(e));
        }
        SipHashFunction(static_cast<void*>(local.Data()), local.Size(),
                        static_cast<void*>(key.Data()), static_cast<uint8_t*>(out.Data()),
                        out.Size());
        return out;
    }
};
template <typename Function, typename Key, typename ReturnValue>
struct Hash {
    ReturnValue operator()(Key const& s) const noexcept { return Function()(s); }
};
template <>
struct Hash<MurmurHash3<ByteBuffer, size_t>, ByteBuffer, ByteBuffer> {
    size_t operator()(ByteBuffer const& s) const noexcept { return 0; };

};  // namespace tsfile
using ByteMurmurHash3 = Hash<MurmurHash3<ByteBuffer, ByteBuffer>, ByteBuffer, ByteBuffer>;
using ByteSipHash = Hash<SipHash, ByteBuffer, ByteBuffer>;  //
/*
template <Serializable T>
struct ObjectHasher {
    std::string operator()(Serializable T& value) {
        ByteBuffer outbuffer;
        std::apply(
            [&outbuffer](Serializable const&... tupleArgs) {
                size_t tsize = std::tuple_size(tupleArgs);
                for (size_t i = 0; i < tsize; i++) {
                    auto val = std::get<i>(tupleArgs);
                    outbuffer.Append(val);
                }
            },
            value.Members());
        auto hashBuffer = ByteSipHash{}(outbuffer);
        return hashBuffer.Hex();
    }
};
*/
}  // namespace tsfile
#endif
