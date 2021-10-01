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
#if 0

#include "tsfile/model/chunk.h"

#include "tsfile/common/hasher.h"
#include "tsfile/common/util.h"

namespace iotdb::tsfile {

bool operator==(const chunk& lhs, const chunk& rhs) { return lhs.hash_code() == rhs.hash_code(); }

chunk::chunk(const iotdb::tsfile::ChunkHeader& header, const std::byte& marker)
    : _header(header), _marker(marker) {}

ChunkHeader chunk::header() const noexcept { return _header; }
std::byte chunk::marker() const noexcept { return _marker; }
void chunk::add_page(iotdb::tsfile::page&& source) {
    _pages.push_back(std::move(source));
    hasher hasher;
    hasher.add(_header.hash_code());
    hasher.add(_marker);
    for (const auto& page : _pages) {
        hasher.add(page.hash_code());
    }
    _hash_code = hasher.compute();
}
bool chunk::remove_page(const iotdb::tsfile::page& page) {
    auto ret = iotdb::util::RemoveUsingHash(_pages, page);
    if (ret) {
        hasher hasher;
        hasher.add(_header.hash_code());
        hasher.add(_marker);
        for (const auto& page : _pages) {
            hasher.add(page.hash_code());
        }
        _hash_code = hasher.compute();
    }
    return ret;
}

page_iterator chunk::begin() { return _pages.begin(); }
page_iterator chunk::end() { return _pages.end(); }
const_page_iterator chunk::cbegin() const { return _pages.cbegin(); }
const_page_iterator chunk::cend() const { return _pages.cend(); }
reverse_page_iterator chunk::rbegin() { return _pages.rbegin(); }
reverse_page_iterator chunk::rend() { return _pages.rend(); }
const_reverse_page_iterator chunk::crbegin() const { return _pages.crbegin(); }
const_reverse_page_iterator chunk::crend() const { return _pages.crend(); }
uint64_t chunk::hash_code() const { return _hash_code; }

};  // namespace iotdb::tsfile
#endif