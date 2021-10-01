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
#include <tsfile/common/concepts.h>
#include <tsfile/model/chunk_header.h>
#include <tsfile/model/page.h>

#include <cstddef>
#include <memory>
#include <numeric>
#include <vector>

namespace iotdb::tsfile {

/// @brief Class that holds the responsibility to model a chunk
///
class Chunk {
   public:
    using iterator = std::vector<iotdb::tsfile::Page>::iterator;
    using const_iterator = std::vector<iotdb::tsfile::Page>::const_iterator;
    using reverse_iterator = std::vector<iotdb::tsfile::Page>::reverse_iterator;
    using const_reverse_iterator = std::vector<iotdb::tsfile::Page>::const_reverse_iterator;
    using UniquePagePtr = std::unique_ptr<iotdb::tsfile::Page>;
    using Byte = iotdb::tsfile::common::Byte;

    ///
    /// @brief Constructor
    /// @param header header of the chunk
    /// @param marker marker
    ///
    Chunk(iotdb::tsfile::ChunkHeader&& header, const Byte& marker);
    ///
    /// @brief Equality comparison operator
    ///
    template <Hashable>
    friend bool operator==(const Hashable auto& lhs, const Hashable auto& rhs);
    ///
    /// @brief Ordering comparison operator
    template <Hashable>
    friend bool operator>(const Hashable auto& lhs, const Hashable auto& rhs);

    ///
    ///  @brief Return the header.
    ///  @return the header of chunk
    ChunkHeader Header() const noexcept;
    ///
    /// @brief Return the file marker
    /// @return marker of the chunk
    Byte Marker() const noexcept;
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
    iterator begin();
    ///
    /// @brief Page forward  mark iterator
    ///
    iterator end();
    ///
    /// @brief Page const forward iterator
    ///
    const_iterator cbegin() const;
    ///
    /// @brief Page forward  mark iterator
    ///
    const_iterator cend() const;
    ///
    /// @brief Page backward iterator
    ///
    reverse_iterator rbegin();
    ///
    /// @brief Page backward mark iterator
    ///
    reverse_iterator rend();
    ///
    /// @brief Reverse const forward iterator
    ///
    const_reverse_iterator crbegin() const;
    ///
    /// @brief Reverse const forward iterator
    ///
    const_reverse_iterator crend() const;
    /// @brief Object hash
    ///
    uint64_t HashCode() const;

   private:
    iotdb::tsfile::ChunkHeader header_;
    iotdb::tsfile::common::Byte marker_{0};
    std::vector<iotdb::tsfile::Page> pages_;
    uint64_t hash_code_{0};
};

}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_H
