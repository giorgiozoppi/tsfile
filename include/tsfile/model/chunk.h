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
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

namespace tsfile {

/// @brief An errorchunk indicates the operation related to a chunk/chunkgroup
enum class ErrorChunk {
    OK,               ///< The operation on a chuck has been successfully.
    CHUNK_NOT_FOUND,  ///< The search on a chunk group failed.
    PAGE_NOT_FOUND,   ///<  The page has not been found in a chunk.
    HEADER_INVALID    ///<  The header is invalid.
};
/// @brief Class that holds the responsibility to model a chunk
///
class Chunk {
   public:
    using iterator = std::vector<Page>::iterator;
    using const_iterator = std::vector<Page>::const_iterator;
    using reverse_iterator = std::vector<Page>::reverse_iterator;
    using const_reverse_iterator = std::vector<Page>::const_reverse_iterator;
    using unique_page_ptr = std::unique_ptr<Page>;
    /*
        Chunk(const Chunk& source) {
            header_ = source.header_;
            marker_ = source.marker_;
            pages_ = source.pages_;
            hash_code_ = source.hash_code_;
            std::cout << "Copy" << std::endl;
        }
        Chunk& operator=(const Chunk& source) {
            if (this != &source) {
                header_ = source.header_;
                marker_ = source.marker_;
                pages_ = source.pages_;
                hash_code_ = source.hash_code_;
                std::cout << "Copy Assign" << std::endl;
            }
            return *this;
        }
        Chunk(Chunk&& source) {
            header_ = std::move(source.header_);
            marker_ = std::move(source.marker_);
            pages_ = std::move(source.pages_);
            hash_code_ = std::move(source.hash_code_);
            std::cout << "Move" << std::endl;
        }
        Chunk& operator=(Chunk&& source) {
            if (this != &source) {
                header_ = std::move(source.header_);
                marker_ = std::move(source.marker_);
                pages_ = std::move(source.pages_);
                hash_code_ = std::move(source.hash_code_);
                std::cout << "Copy Assign" << std::endl;
            }
            return *this;
        } */
    ~Chunk() = default;
    /// nsructor
    ///  @paramth chunk
    ///
    explicit Chunk(ChunkHeader&& header, const Byte& marker);
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
    ChunkHeader GetHeader() const noexcept;
    ///
    /// @brief Return the file marker
    /// @return marker of the chunk
    Byte GetMarker() const noexcept;
    ///
    /// @brief Add a page to the chunk.
    /// @param page to add.
    ///
    void AddPage(Page&& page);
    ///
    /// @brief Remove a page from a chunk
    /// @param page to remove.
    bool RemovePage(const Page& page);
    //// @brief Page forward iterator
    ///
    iterator begin();
    /// geforward  mark iterator
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
    uint64_t GetHashCode() const;
    /// @brief Get the number of pages
    /// @return the number of pages
    ///
    size_t GetNumOfPages() const;

    EXPOSE_MEMBERS(header_, marker_, pages_);

   private:
    void ComputeHash();
    ChunkHeader header_;
    Byte marker_{0};
    std::vector<Page> pages_;
    uint64_t hash_code_{0};
};

}  // namespace tsfile
#endif
