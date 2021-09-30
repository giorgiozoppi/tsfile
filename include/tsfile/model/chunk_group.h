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

#ifndef IOTDB_NATIVE_CHUNK_GROUP_H
#define IOTDB_NATIVE_CHUNK_GROUP_H
#include <cstddef>
#include <memory>
#include <vector>

#include "chunk.h"
#include "chunk_group_footer.h"
namespace iotdb::tsfile {
using ChunkIterator = std::vector<iotdb::tsfile::Chunk>::iterator;
using ReverseChunkIterator = std::vector<iotdb::tsfile::Chunk>::reverse_iterator;
using ConstChunkIterator = std::vector<iotdb::tsfile::Chunk>::const_iterator;
using ConstReverseChunkIterator = std::vector<iotdb::tsfile::Chunk>::const_reverse_iterator;

class ChunkGroup {
   public:
    std::byte Delimiter() const;
    void AddChunk(iotdb::tsfile::Chunk&& chunk);
    bool RemoveChunk(const iotdb::tsfile::Chunk& chunk);
    ChunkGroupFooter Footer() const;
    ChunkIterator begin();
    ChunkIterator end();
    ReverseChunkIterator rbegin();
    ReverseChunkIterator rend();
    ConstChunkIterator cbegin() const;
    ConstChunkIterator cend() const;
    ConstReverseChunkIterator crbegin() const;
    ConstReverseChunkIterator crend() const;

   private:
    std::vector<iotdb::tsfile::Chunk> chunks_;
    std::byte byte_delimiter_;
    ChunkGroupFooter footer_;
};
}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_GROUP_H
