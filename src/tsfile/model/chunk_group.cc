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
#include <tsfile/common/common.h>
#include <tsfile/common/algorithm.h>
#include <tsfile/model/chunk_group.h>
#include <tsfile/model/chunk_group_footer.h>

namespace tsfile {
ChunkGroup::ChunkGroup(ChunkGroupFooter&& group, Byte delim)
    : footer_(std::move(group)), byte_delimiter_(delim) {}
ChunkGroup::ChunkGroup(const ChunkGroupFooter& group, Byte delim)
    : footer_(group), byte_delimiter_(delim) {}
ChunkGroupFooter ChunkGroup::Footer() const { return footer_; }
ChunkGroup::iterator ChunkGroup::begin() { return chunks_.begin(); }
ChunkGroup::iterator ChunkGroup::end() { return chunks_.end(); }
size_t ChunkGroup::Size() const { return chunks_.size(); }
ChunkGroup::reverse_iterator ChunkGroup::rbegin() { return chunks_.rbegin(); }
ChunkGroup::reverse_iterator ChunkGroup::rend() { return chunks_.rend(); }
ChunkGroup::const_iterator ChunkGroup::cbegin() const { return chunks_.cbegin(); }
ChunkGroup::const_iterator ChunkGroup::cend() const { return chunks_.cend(); }
void ChunkGroup::AddChunk(Chunk&& chunk) { chunks_.emplace_back(std::move(chunk)); }
Expected<ErrorChunk, Chunk>  ChunkGroup::RemoveChunk(size_t pos) {
    if (pos >= chunks_.size()) {
        return Expected<ErrorChunk, Chunk>(ErrorChunk::CHUNK_NOT_FOUND);
    }
    auto v = chunks_[pos];
    chunks_.erase(chunks_.begin()+pos);
    return Expected<ErrorChunk, Chunk>(ErrorChunk::OK, v);
} 
bool ChunkGroup::RemoveChunk(const Chunk& input) { return EraseUsingHash(chunks_, input); }
Byte ChunkGroup::Delimiter() const { return byte_delimiter_; }
ChunkGroup::const_reverse_iterator ChunkGroup::crbegin() const { return chunks_.crbegin(); }
ChunkGroup::const_reverse_iterator ChunkGroup::crend() const { return chunks_.crend(); }
}  // namespace tsfile
