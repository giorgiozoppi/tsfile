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

#include <tsfile/common/algorithm.h>
#include <tsfile/model/chunk.h>

namespace tsfile {

Chunk::Chunk(ChunkHeader&& header, const Byte& marker)
    : header_(std::move(header)), marker_(marker) {}

ChunkHeader Chunk::Header() const noexcept { return header_; }
Byte Chunk::Marker() const noexcept { return marker_; }
void Chunk::AddPage(Page&& source) {
    pages_.push_back(std::move(source));
    header_.SetNumOfPages(header_.NumOfPages() +1);
    hash_code_ = 10219219280182L;
}
bool Chunk::RemovePage(const Page& page) {
    return EraseUsingHash(pages_, page);
}
size_t Chunk::NumOfPages() const  {
    return pages_.size();
}
Chunk::iterator Chunk::begin() { return pages_.begin(); }
Chunk::iterator Chunk::end() { return pages_.end(); }
Chunk::const_iterator Chunk::cbegin() const { return pages_.cbegin(); }
Chunk::const_iterator Chunk::cend() const { return pages_.cend(); }
Chunk::reverse_iterator Chunk::rbegin() { return pages_.rbegin(); }
Chunk::reverse_iterator Chunk::rend() { return pages_.rend(); }
Chunk::const_reverse_iterator Chunk::crbegin() const { return pages_.crbegin(); }
Chunk::const_reverse_iterator Chunk::crend() const { return pages_.crend(); }
uint64_t Chunk::HashCode() const { return  hash_code_; } 
};  // n_amespace iotdb::tsfile
