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

class Chunk {
   public:
    Chunk(iotdb::tsfile::ChunkHeader&& header, const std::byte& marker);
    friend bool operator==(const Chunk& lhs, const Chunk& rhs);
    friend bool operator<(const Chunk& lhs, const Chunk& rhs);
    friend bool operator==(const Chunk& lhs, const Chunk& rhs);

    // getter
    ChunkHeader Header() const noexcept;
    std::byte Marker() const noexcept;
    // add a Page to a chunk.
    void AddPage(iotdb::tsfile::Page&& Page);
    bool RemovePage(const iotdb::tsfile::Page& Page);
    // Page interator
    PageIterator begin();
    PageIterator end();
    ConstPageIterator cbegin() const;
    ConstPageIterator cend() const;
    ReversePageIterator rbegin();
    ReversePageIterator rend();
    ConstReversePageIterator crbegin() const;
    ConstReversePageIterator crend() const;
    uint64_t HashCode() const;

   private:
    iotdb::tsfile::ChunkHeader header_;
    std::byte marker_{0};
    std::vector<iotdb::tsfile::Page> pages_;
    uint64_t hash_code_{0};
};

}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_H
