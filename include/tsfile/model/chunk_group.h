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
///
/// @brief A ChunkGroup stores the data of an entity for a period of time.
//  It consists of several Chunk, a byte delimiter 0x00 and a ChunkFooter.
///
class ChunkGroup {
   public:
    ///
    /// @brief  Return the chunk delimiter
    ///
    /// @return Chunk delimiter
    std::byte Delimiter() const;
    ///
    /// @brief  Add a new chunk to the chunkgroup, transfer ownership
    ///
    /// @return chunk Chunk
    void AddChunk(iotdb::tsfile::Chunk&& chunk);
    ///
    /// @brief Remove a chunk from the chunkgroup
    ///
    /// @return true if it's removed.
    bool RemoveChunk(const iotdb::tsfile::Chunk& chunk);
    ///
    /// @brief Get the chunk group footer
    ///
    /// @return Chunk group footer.
    ChunkGroupFooter Footer() const;
    ///
    /// @brief Iterator

    /// @return Iterator
    ChunkIterator begin();
    ///
    /// @brief Iterator marker
    /// @return Iterator marker

    ChunkIterator end();
    ///
    /// @brief Reverse Iterator
    /// @return reverse iterator
    ReverseChunkIterator rbegin();
    ///
    /// @brief Reverse Iterator marker
    /// @return reverse iterator
    ReverseChunkIterator rend();
    ///
    /// @brief  Const Iterator
    ///
    ConstChunkIterator cbegin() const;
    ///
    /// @brief Const Iterator
    ///
    ConstChunkIterator cend() const;
    ///
    /// @brief Reverse Const Iterator
    ///
    ConstReverseChunkIterator crbegin() const;
    ///
    /// @brief Reverse Const Iterator
    ///
    ConstReverseChunkIterator crend() const;

   private:
    std::vector<iotdb::tsfile::Chunk> chunks_;
    std::byte byte_delimiter_;
    ChunkGroupFooter footer_;
};
}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_GROUP_H
