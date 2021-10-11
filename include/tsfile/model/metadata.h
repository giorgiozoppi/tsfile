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
#include <tsfile/model/statistics.h>

#include <memory>
#include <string>
#include <tuple>

namespace tsfile {

typedef std::tuple<std::string, int64_t> MetadataIndexEntry;

enum class MetadataIndexNodeType {
    INTERNAL_DEVICE = 0,
    LEAF_DEVICE = 1,
    INTERNAL_MEASUREMENT = 2,
    LEAF_MEASUREMENT = 3
};

class ChunkMetadataComponent {
    virtual StatisticsMap* Statistics() const = 0;

    boolIsModified() const = 0;

    void setModified(boolean modified);

    boolean isSeq();

    void setSeq(boolean seq);

    long getVersion();

    void setVersion(long version);

    long getOffsetOfChunkHeader();

    long getStartTime();

    long getEndTime();

    boolean isFromOldTsFile();

    IChunkLoader getChunkLoader();

    boolean needSetChunkLoader();

    void setChunkLoader(IChunkLoader chunkLoader);

    void setFilePath(String filePath);

    void setClosed(boolean closed);

    TSDataType getDataType();

    String getMeasurementUid();

    void insertIntoSortedDeletions(long startTime, long endTime);

    List<TimeRange> getDeleteIntervalList();

    int serializeTo(OutputStream outputStream, boolean serializeStatistic) throws IOException;

    byte getMask();

    boolean isTimeColumn();

    boolean isValueColumn();
};
class ChunkMetadata : public ChunkMetadataComponent {}

};
class ChunkMetadataComposite : public ChunkMetadataComponent {};

class MetadataIndexNode {
   public:
    MetadataIndexNode(std::vector<std::unique_ptr<MetadataIndexEntry>>&& children, int64_t offset,
                      MetadataIndexNodeType node_type)
        : children_(std::move(children)), end_offset_(offset), node_type_(node_type) {}
    MetadataIndexNode(const std::vector<std::unique_ptr<MetadataIndexEntry>>& children,
                      int64_t offset, MetadataIndexNodeType node_type)
        : children_(std::move(children)), end_offset_(offset), node_type_(node_type) {}
    MetadataIndexNode(const MetadataIndexNodeType& node_type) : node_type_(node_type) {}

   private:
    std::vector<std::unique_ptr<MetadataIndexEntry>> children_;
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