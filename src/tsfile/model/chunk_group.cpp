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
#include <tsfile/model/chunk_group.h>

namespace iotdb::tsfile {
std::byte ChunkGroup::delimiter() const { return _byte_delimiter; }
chunk_group_footer ChunkGroup::footer() const { return _footer; }
chunk_iterator ChunkGroup::begin() { return _chunks.begin(); }
chunk_iterator ChunkGroup::end() { return _chunks.end(); }
reverse_chunk_iterator ChunkGroup::rbegin() { return _chunks.rbegin(); }
reverse_chunk_iterator ChunkGroup::rend() { return _chunks.rend(); }
const_chunk_iterator ChunkGroup::cbegin() const { return _chunks.cbegin(); }
const_chunk_iterator ChunkGroup::cend() const { return _chunks.cend(); }
void ChunkGroup::add_chunk(iotdb::tsfile::chunk&& chunk) { _chunks.push_back(std::move(chunk)); }
bool ChunkGroup::remove_chunk(const iotdb::tsfile::chunk& input) {
    return true;
}

const_reverse_chunk_iterator ChunkGroup::crbegin() const { return _chunks.crbegin(); }
const_reverse_chunk_iterator ChunkGroup::crend() const { return _chunks.crend(); }
}  // namespace iotdb::tsfile
#endif
