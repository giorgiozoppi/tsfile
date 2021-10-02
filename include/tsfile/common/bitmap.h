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

#include <bitset>
#include <cstddef>
#include <cstring>
#include <memory>

namespace tsfile {
///
/// @brief A bitmap is a variable array of bits. It can be constructed from a generic set of bytes.
///
class BitMap {
   public:
    ///
    /// @brief Constructor
    /// @param size number of bytes of the bitmap
    ///
    explicit BitMap(const size_t& size);
    ///
    /// @brief Bitmap copy constructor
    /// @param map instance to copy
    ///

    explicit BitMap(const BitMap& map);

    ///
    ///  @brief Bitmap copy operator
    ///  @param Bitmap to copy
    ///  @return a copy of the original Bitmap
    ///

    BitMap& operator=(const BitMap& map);

    ///
    /// @brief BitMap move constructor
    /// @param  BitMap moveable object.
    ///

    BitMap(BitMap&& b);

    ///
    ///  @brief BitMap move assignemnt operator
    ///  @param BitMap to move
    ///  @return a copy of the original BitMap

    BitMap& operator=(BitMap&& map);

    ///
    /// @brief Set a bit in the BitMap
    /// @param pos position to be set.
    /// @return A tuple of value and bitmap

    StatusResult<BitError> Mark(size_t index);

    ///
    /// @brief Mark all bits to 1.
    /// @return If the operation has been successfully
    ///

    StatusResult<BitError> MarkAll();
    ///
    /// @brief Reset all bitmaps.
    /// @return If the operation has been successfully
    ///

    StatusResult<BitError> Reset();

    ///
    /// @brief Set a bit to zero the BitMap
    /// @param pos position to be set.
    /// @return A tuple of value and bitmap

    StatusResult<BitError> UnMark(size_t index);

    ///
    /// @brief Access to the a bit in a position;
    /// @param index position in the bitmap to retrieve.
    /// @return A tuple ValueResult = (error, bit value).

    ValueResult<BitError, short> operator[](size_t index) const;
    ///
    /// @brief Destructor
    ///
    ~BitMap() = default;  // to respect the rule of 5

   private:
    friend bool operator==(const BitMap& lhs, const BitMap& rhs);
    size_t count_;
    std::unique_ptr<Byte[]> bytes_;
};

}  // namespace tsfile
#endif
