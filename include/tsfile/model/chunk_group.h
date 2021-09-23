/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef IOTDB_NATIVE_CHUNK_GROUP_H
#define IOTDB_NATIVE_CHUNK_GROUP_H
#include <cstddef>
#include <memory>
#include <vector>

#include "model/chunk.h"
#include "model/chunk_group_footer.h"
namespace iotdb::tsfile {
using chunk_iterator = std::vector<iotdb::tsfile::chunk>::iterator;
using reverse_chunk_iterator = std::vector<iotdb::tsfile::chunk>::reverse_iterator;
using const_chunk_iterator = std::vector<iotdb::tsfile::chunk>::const_iterator;
using const_reverse_chunk_iterator = std::vector<iotdb::tsfile::chunk>::const_reverse_iterator;

class chunk_group {
    std::vector<iotdb::tsfile::chunk> _chunks;
    std::byte _byte_delimiter;
    chunk_group_footer _footer;

   public:
    std::byte delimiter() const;
    void add_chunk(iotdb::tsfile::chunk&& chunk);
    bool remove_chunk(const iotdb::tsfile::chunk& chunk);
    chunk_group_footer footer() const;
    chunk_iterator begin();
    chunk_iterator end();
    reverse_chunk_iterator rbegin();
    reverse_chunk_iterator rend();
    const_chunk_iterator cbegin() const;
    const_chunk_iterator cend() const;
    const_reverse_chunk_iterator crbegin() const;
    const_reverse_chunk_iterator crend() const;
};
}  // namespace iotdb::tsfile

#endif  // TSFILE_CHUNK_GROUP_H
