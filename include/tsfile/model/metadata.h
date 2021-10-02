/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef IOTDB_MODEL_METADATA
#define IOTDB_MODEL_METADATA

#include <tsfile/common/bloomfilter.h>

#include <memory>
#include <string>
#include <tuple>

namespace tsfile {

typedef std::tuple<std::string, int64_t> MetadataIndexEntry;

class MetadataIndexNodeType {};

class MetadataIndexNode {
   public:
    using internal_buffer = typename std::vector<MetadataIndexEntry>;
    using value_type = MetadataIndexEntry;
    using iterator = typename internal_buffer::iterator;
    using reverse_iterator = typename internal_buffer::reverse_iterator;
    using const_reverse_iterator = typename internal_buffer::const_reverse_iterator;
    using const_iterator = typename internal_buffer::const_iterator;

   private:
    std::vector<MetadataIndexEntry> children_;
    int64_t end_offset_;

    MetadataIndexNodeType node_type_;
};

///
/// @brief TSFileMetaData collects all metadata info and saves in its data structure.
///
class TsFileMetadata {
   private:
    // bloom filter
    std::unique_ptr<BloomFilter> bloom_filter_;
    // List of <name, offset, childMetadataIndexType>
    std::unique_ptr<MetadataIndexNode> metadata_index_;
    // offset of MetaMarker.SEPARATOR
    uint64_t meta_offset_;
};
}  // namespace tsfile
#endif