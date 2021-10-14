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

#include <tsfile/common/common.h>
#include <tsfile/model/chunk.h>
#include <tsfile/model/chunk_group_footer.h>

#include <cstddef>
#include <memory>
#include <vector>
namespace tsfile {
///
/// @brief A ChunkGroup stores the data of an entity for a period of time.
//  It consists of several Chunk, a byte delimiter 0x00 and a ChunkFooter.
///
class ChunkGroup {
   public:
    using iterator = std::vector<Chunk>::iterator;
    using reverse_iterator = std::vector<Chunk>::reverse_iterator;
    using const_iterator = std::vector<Chunk>::const_iterator;
    using const_reverse_iterator = std::vector<Chunk>::const_reverse_iterator;
    ChunkGroup(const ChunkGroupFooter& group, Byte delim);
    ///
    /// @brief Constructor
    /// @param group group footer
    /// @param delim chunk group delimiter.
    ///
    ChunkGroup(ChunkGroupFooter&& group, Byte delim);
    ///
    /// @brief  Return the chunk delimiter
    ///
    /// @return Chunk delimiter
    Byte GetDelimiter() const;
    ///
    /// @brief  Add a new chunk to the chunkgroup, transfer ownership
    ///
    /// @return chunk Chunk
    void AddChunk(Chunk&& chunk);
    ///
    /// @brief Remove a chunk from the chunkgroup
    ///
    /// @return true if it's removed.
    bool RemoveChunk(const Chunk& chunk);
    ///
    /// @brief Remove a chunk by index and returns the chunk removed or an error
    /// @param pos Position in the chunk
    Expected<ErrorChunk, Chunk> RemoveChunk(size_t pos);
    ///
    /// @brief Return the size
    /// @return the return the number of items.
    ///
    size_t GetSize() const;
    ///
    /// @brief Get the chunk group footer
    ///
    /// @return Chunk group footer.
    ChunkGroupFooter GetFooter() const;
    ///
    /// @brief Iterator

    /// @return Iterator
    iterator begin();
    ///
    /// @brief Iterator marker
    /// @return Iterator marker

    iterator end();
    ///
    /// @brief Reverse Iterator
    /// @return reverse iterator
    reverse_iterator rbegin();
    ///
    /// @brief Reverse Iterator marker
    /// @return reverse iterator
    reverse_iterator rend();
    ///
    /// @brief  Const Iterator
    ///
    const_iterator cbegin() const;
    ///
    /// @brief Const Iterator
    ///
    const_iterator cend() const;
    ///
    /// @brief Reverse Const Iterator
    ///
    const_reverse_iterator crbegin() const;
    ///
    /// @brief Reverse Const Iterator
    ///
    const_reverse_iterator crend() const;

    EXPOSE_MEMBERS(chunks_, footer_, byte_delimiter_)

   private:
    std::vector<Chunk> chunks_;
    ChunkGroupFooter footer_;
    Byte byte_delimiter_;
};
}  // namespace tsfile

#endif  // TSFILE_CHUNK_GROUP_H
