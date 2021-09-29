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

namespace iotdb::tsfile::common {

BitMap::BitMap(const size_t& siz) : count_(siz) { 
    auto num_bytes = std::round(count_/8.0);

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

BitMap::BitMap(BitMap&& b) : count_(std::move(b.count_)), bytes_(std::move(b.bytes_))  {}

BitMap& BitMap::operator=(BitMap&& map) {
    if (this != &map) {
        count_= std::move(map.count_);
        bytes_ = std::move(map.bytes_);
    }
    return *this;
}
ValueResult<BitError, BitMap> BitMap::Set(size_t index) {
    // PRE: shall be lower then len
    auto numbits = count_ * 8;
    if (index < numbits) {
        auto pos = (count_ * 8 )/ index;
        auto rest = (count_ * 8 ) % index;
        bytes_[pos]
        return ValueResult<BitError, BitMap>(BitError::OUT_RANGE, *this);
    }
    return ValueResult<BitError, BitMap>(BitError::OUT_RANGE, *this);
}

ValueResult<BitError, std::bitset<1>> BitMap::operator[](size_t index) const {
    if (index < count_) {
        return ValueResult<BitError, std::bitset<1>>(BitError::OUT_RANGE, std::bitset<1>());
    }
    return ValueResult<BitError, std::bitset<1>>(BitError::OUT_RANGE, std::bitset<1>());
}
    
}  // namespace iotdb::tsfile::common
