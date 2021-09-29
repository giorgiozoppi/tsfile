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
#ifndef IOTDB_NATIVE_CHUNK_H
#define IOTDB_NATIVE_CHUNK_H

#include <tsfile/model/chunk_header.h>
#include <tsfile/model/page.h>

#include <cstddef>
#include <memory>
#include <numeric>
#include <vector>

namespace iotdb::tsfile {
using page_iterator = std::vector<iotdb::tsfile::page>::iterator;
using const_page_iterator = std::vector<iotdb::tsfile::page>::const_iterator;
using reverse_page_iterator = std::vector<iotdb::tsfile::page>::reverse_iterator;
using const_reverse_page_iterator = std::vector<iotdb::tsfile::page>::const_reverse_iterator;
using unique_page_ptr = std::unique_ptr<iotdb::tsfile::page>;

class chunk {
    //iotdb::tsfile::ChunkHeader _header;
    std::byte _marker{0};
    std::vector<iotdb::tsfile::page> _pages;
    uint64_t _hash_code{0};

   public:
   Chunk() {}
  //  chunk(const iotdb::tsfile::ChunkHeader& header, const std::byte& marker);
    friend bool operator==(const chunk& lhs, const chunk& rhs);
    friend bool operator<(const chunk& lhs, const chunk& rhs);
    friend bool operator==(const chunk& lhs, const chunk& rhs);

    // getter
//    ChunkHeader header() const noexcept;
    std::byte marker() const noexcept;
    // add a page to a chunk.
    void add_page(iotdb::tsfile::page&& page);
    bool remove_page(const iotdb::tsfile::page& page);
    // page interator
    page_iterator begin();
    page_iterator end();
    const_page_iterator cbegin() const;
    const_page_iterator cend() const;
    reverse_page_iterator rbegin();
    reverse_page_iterator rend();
    const_reverse_page_iterator crbegin() const;
    const_reverse_page_iterator crend() const;
    uint64_t hash_code() const;
};

}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_H
#endif
