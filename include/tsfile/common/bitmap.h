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
#ifndef IOTDB_TSFILE_COMMON_BITMAP
#define IOTDB_TSFILE_COMMON_BITMAP
#include <cstddef>
#include <cstring>
#include <memory>
#include <tsfile/common/common.h>

namespace io::tsfile::common {
///
/// @brief A bitmap is a variable array of bits. It can be constructed from a generic set of bytes.
///
class BitMap {

   public:
    ///
    /// @brief BitMap constructor
    /// @param size   number of bytes of the array.
    ///
    ///explicit BitMap(size_t size) : len_(size) { bytes_ = std::make_unique<Byte[]>(size); }
    #if 0
    ///
    /// @brief Bitmap constructor
    /// @param buffer   ByteArray to copy from.
    ///
    explicit BitMap(const std::initializer_list<io::tsfile::common::Byte>& buffer) {
        bytes_ = std::make_unique<io::tsfile::common::Byte[]>(buffer.size());
        // std::memcpy(*bytes_, buffer.data(), buffer.size());
    }

    ///
    /// @brief Bitmap copy constructor
    /// @param map instance to copy
    ///
    BitMap(const BitMap& map) {
        if (this != &map) {
            bytes_ = std::make_unique<io::tsfile::common::Byte[]>(map.len_);
            std::memcpy(*_bytes, *map.bytes_, map.len_);
        }
    }
    ///
    ///  @brief Bitmap copy operator
    ///  @param Bitmap to copy
    ///  @return a copy of the original Bitmap

    BitMap& operator=(const BitMap& map) {
        if (this != &map) {
            bytes_ = std::make_unique<io::tsfile::common::Byte[]>(map.len_);
            len_ = map.len_;
            std::memcpy(*_bytes, *map.len_, map.len_);
        }
    }

    ///
    /// @brief BitMap move constructor
    /// @param  BitMap moveable object.
    ///

    BitMap(BitMap&& b) : bytes_(std::move(b.bytes_)), len_(std::move(b.len_)) {}

    ///
    ///  @brief BitMap move assignemnt operator
    ///  @param BitMap to move
    ///  @return a copy of the original BitMap

    BitMap& operator=(BitMap&& map) {
        if (this != &map) {
            bytes_ = std::move(map.bytes_);
            len_ = std::move(map.len_);
        }
    }
    ///
    /// @brief Set a bit in the BitMap
    /// @param pos position to be set.
    /// 
    bool Set(uint64_t index) { return true; }
    ///
    /// @brief MarkSet Set all bits in the BitMap to 1.
    ///
    void MarkSet() {}
    ///
    /// @brief MarkSet Set all bits in the BitMap to 0.
    ///
    void Clear() {}

    ~BitMap() {}
    ///
    /// @brief Size in number o bits
    /// @return Number of bits
    ///
    const size_t Size() const { return len_; }
#endif
   private:
    /// std::unique_ptr<Byte> bytes_;
    size_t len_;
};
}  // namespace io::tsfile::common
#endif
