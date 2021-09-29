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
#ifndef IOTDB_NATIVE_COMMON_BITMAP
#define IOTDB_NATIVE_COMMON_BITMAP
#include <tsfile/common/common.h>

#include <cstddef>
#include <cstring>
#include <memory>

namespace iotdb::tsfile::common {
///
/// @brief A bitmap is a variable array of bits. It can be constructed from a generic set of bytes.
///
class BitMap {
   public:
    ///
    /// @brief Constructor
    /// @param size size of the bitMap
    ///
    explicit BitMap(size_t size) : count_(size) { bytes_ = std::make_unique<Byte[]>(size); }
    ///
    /// @brief Bitmap copy constructor
    /// @param map instance to copy
    ///

    explicit BitMap(const BitMap& map) {
        if (this != &map) {
            bytes_ = std::make_unique<Byte[]>(map.count_);
            std::memcpy(bytes_.get(), map.bytes_.get(), map.count_);
        }
    }

    ///
    ///  @brief Bitmap copy operator
    ///  @param Bitmap to copy
    ///  @return a copy of the original Bitmap
    ///

    BitMap& operator=(const BitMap& map) {
        if (this != &map) {
            bytes_ = std::make_unique<Byte[]>(map.count_);
            std::memcpy(bytes_.get(), map.bytes_.get(), map.count_);
        }
        return *this;
    }

   private:
    size_t count_;
    std::unique_ptr<Byte[]> bytes_;
};

}  // namespace iotdb::tsfile::common
#endif
