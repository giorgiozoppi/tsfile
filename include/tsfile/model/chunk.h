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
#ifndef IOTDB_NATIVE_CHUNK_H
#define IOTDB_NATIVE_CHUNK_H

#include <tsfile/common/common.h>
#include <tsfile/model/chunk_header.h>
#include <tsfile/model/page.h>

#include <cstddef>
#include <memory>
#include <numeric>
#include <vector>

namespace iotdb::tsfile {
using PageIterator = std::vector<iotdb::tsfile::Page>::iterator;
using ConstPageIterator = std::vector<iotdb::tsfile::Page>::const_iterator;
using ReversePageIterator = std::vector<iotdb::tsfile::Page>::reverse_iterator;
using ConstReversePageIterator = std::vector<iotdb::tsfile::Page>::const_reverse_iterator;
using UniquePagePtr = std::unique_ptr<iotdb::tsfile::Page>;
///
/// @brief Class that holds the responsibility to model a chunk
///
class Chunk {
   public:
    ///
    /// @brief Constructor
    /// @param header header of the chunk
    /// @param marker marker
    ///
    Chunk(iotdb::tsfile::ChunkHeader&& header, const Byte& marker) noexcept;
    ///
    /// @brief Equality comparison operator
    ///
    friend bool operator==(const Chunk& lhs, const Chunk& rhs);
    ///
    /// @brief Ordering comparison operator
    ///
    friend bool operator<(const Chunk& lhs, const Chunk& rhs);
    ///
    /// @brief Ordering comparison operator
    ///
    friend bool operator==(const Chunk& lhs, const Chunk& rhs);

    ///
    ///  @brief Return the header.
    ///  @return the header of chunk
    ChunkHeader Header() const noexcept;
    ///
    /// @brief Return the file marker
    /// @return marker of the chunk
    std::byte Marker() const noexcept;
    ///
    /// @brief Add a page to the chunk.
    /// @param page to add.
    ///
    void AddPage(iotdb::tsfile::Page&& page);
    ///
    /// @brief Remove a page from a chunk
    /// @param page to remove.
    bool RemovePage(const iotdb::tsfile::Page& page);
    ///
    /// @brief Page forward iterator
    ///
    PageIterator begin();
    ///
    /// @brief Page forward  mark iterator
    ///
    PageIterator end();
    ///
    /// @brief Page const forward iterator
    ///
    ConstPageIterator cbegin() const;
    ///
    /// @brief Page forward  mark iterator
    ///
    ConstPageIterator cend() const;
    ///
    /// @brief Page backward iterator
    ///
    ReversePageIterator rbegin();
    ///
    /// @brief Page backward mark iterator
    ///
    ReversePageIterator rend();
    ///
    /// @brief Reverse const forward iterator
    ///
    ConstReversePageIterator crbegin() const;
    ///
    /// @brief Reverse const forward iterator
    ///
    ConstReversePageIterator crend() const;
    /// @brief Object hash
    ///
    uint64_t HashCode() const;

   private:
    iotdb::tsfile::ChunkHeader header_;
    std::byte marker_{0};
    std::vector<iotdb::tsfile::Page> pages_;
    uint64_t hash_code_{0};
};

}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_H
