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
#include <tsfile/common/bitmap.h>

#include <cmath>
#include <iterator>

namespace tsfile {

BitMap::BitMap(const size_t& siz)  {
    auto num_bytes = static_cast<size_t>(std::round(siz / 8.0));
    count_ = num_bytes;
    bytes_ = std::make_unique<Byte[]>(num_bytes);
   
}

BitMap::BitMap(const BitMap& map) {
    if (this != &map) {
        count_ = map.count_;
        bytes_ = std::make_unique<Byte[]>(map.count_);
        std::memcpy(bytes_.get(), map.bytes_.get(), map.count_);
    }
}

BitMap& BitMap::operator=(const BitMap& map) {
    if (this != &map) {
        count_ = map.count_;
        bytes_ = std::make_unique<Byte[]>(map.count_);
        std::memcpy(bytes_.get(), map.bytes_.get(), map.count_);
    }
    return *this;
}

BitMap::BitMap(BitMap&& b) : count_(std::move(b.count_)), bytes_(std::move(b.bytes_)) {}

BitMap& BitMap::operator=(BitMap&& map) {
    if (this != &map) {
        count_ = std::move(map.count_);
        bytes_ = std::move(map.bytes_);
    }
    return *this;
}
StatusResult<BitError> BitMap::Mark(size_t index) {
    auto numbits = count_ * 8;
    if (index < numbits) {
        auto pos = index / 8;
        auto rest_pos = index % 8;
        uint8_t data = static_cast<uint8_t>(std::pow(2, rest_pos));
        auto value = bytes_[pos] | data;
        bytes_[pos] = value;
        return StatusResult<BitError>(BitError::OK);
    }
    return StatusResult<BitError>(BitError::OUT_RANGE);
}
StatusResult<BitError> BitMap::MarkAll() {
     for (size_t i = 0; i < count_; ++i) {
         bytes_.get()[i] = 0xFF;
     }
     return StatusResult<BitError>(BitError::OK); 
}
StatusResult<BitError> BitMap::Reset() {
     for (size_t i = 0; i < count_; ++i) {
         bytes_.get()[i] = 0x00;
     }
     return StatusResult<BitError>(BitError::OK); 
}
ValueResult<BitError, short> BitMap::operator[](size_t index) const {
    auto numbits = count_ * 8;
    if (index < numbits) {
        auto byte_pos = index / 8;
        auto rest_pos = index % 8;
        auto current = bytes_.get()[byte_pos];
        std::bitset<8> v(current);

        return ValueResult<BitError, short>(BitError::OK, v.test(rest_pos) ? 1 : 0);
    }
    return ValueResult<BitError, short>(BitError::OUT_RANGE, 0);
}
///
/// @brief compare two bitmaps
/// @param lhs BitMap to check
/// @param rhs BitMap to check
/// @return value to return
///
bool operator==(const BitMap& lhs, const BitMap& rhs) {
    if (lhs.count_ == rhs.count_) {
        for (size_t i = 0; i < lhs.count_; ++i) {
            if (lhs.bytes_.get()[i] != rhs.bytes_.get()[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}


}  // namespace iotdb::tsfile::common
