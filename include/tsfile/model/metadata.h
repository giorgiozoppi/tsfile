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
#include <tsfile/common/common.h>
#include <tsfile/model/datatypes.h>
#include <tsfile/model/statistics.h>

#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace tsfile {

typedef std::tuple<std::string, int64_t> MetadataIndexEntry;

enum class MetadataIndexNodeType {
    INTERNAL_DEVICE = 0,
    LEAF_DEVICE = 1,
    INTERNAL_MEASUREMENT = 2,
    LEAF_MEASUREMENT = 3
};
class TimeRange {};
class ChunkMetadataComponent {
    virtual ~ChunkMetadataComponent() noexcept = 0;
    virtual std::shared_ptr<StatisticsMap> Statistics() const = 0;

    virtual bool IsModified() const = 0;

    virtual void SetModified(bool modified);

    virtual bool IsSeq() const = 0;

    virtual void SetSeq(bool seq) = 0;

    virtual long GetVersion() const = 0;

    virtual void SetVersion(long version) = 0;

    virtual void long GetOffsetOfChunkHeader() = 0;

    virtual int64_t GetStartTime() const = 0;

    virtual int64_t long GetEndTime() const = 0;

    virtual TSDataType GetDataType() const = 0;

    virtual std::string GetMeasurementUid() = 0;

    virtual std::vector<TimeRange> GetDeleteIntervalList() = 0;

    virtual std::byte GetMask() = 0;

    virtual bool IsTimeColumn() = 0;

    virtual bool IsValueColumn() = 0;
};
class ChunkMetadata : public ChunkMetadataComponent {
    ~ChunkMetadata() noexcept override{};
    std::shared_ptr<StatisticsMap> Statistics() const override;
    bool IsModified() const override;

    void SetModified(bool modified);

    bool IsSeq() const override;

    void SetSeq(bool seq) override;

    long GetVersion() const override;

    void SetVersion(long version) const override;

    long GetOffsetOfChunkHeader() const override;

    int64_t GetStartTime() const override;

    int64_t GetEndTime() const override;

    TSDataType GetDataType() const override;

    std::string GetMeasurementUid() const override;

    std::vector<TimeRange> GetDeleteIntervalList() const override;

    std::byte GetMask() const override;

    bool IsTimeColumn() const override;

    bool IsValueColumn() const override;

   private:
    std::string _measurement_uid;

    /**
     * Byte offset of the corresponding data in the file Notice: include the chunk header and
     * marker.
     */

    int64_t _offset_of_chunk_header;
    TSDataType _ts_data_types;

    /**
     * version is used to define the order of operations(insertion, deletion, update). version is
     * set according to its belonging ChunkGroup only when being queried, so it is not persisted.
     */
    long version;

    /** A list of deleted intervals. */
    std::vector<TimeRange> _delete_interval_list;

    bool _modified;

    /** ChunkLoader of metadata, used to create ChunkReaderWrap */
    /// IChunkLoader chunkLoader;

    StatisticsMap _statistics;

    bool _is_from_old_file{false};

    long _ram_size;
    static constexpr int CHUNK_METADATA_FIXED_RAM_SIZE = 80;

    // used for SeriesReader to indicate whether it is a seq/unseq timeseries metadata
    bool _is_seq{true};
    bool _is_closed{true};
    std::string _file_path;
    Byte _mask;
};
class ChunkMetadataComposite : public ChunkMetadataComponent {
   public:
    ChunkMetadataComposite(std::unique_ptr<IChunkMetadata>&& chunk_metadata,
                           std::vector << IChunkMetadata >> &&chunk_metadatas) {
        time_chunk_metadata_ = chunk_metadata;
        value_chunk_metadata_list_ = valueChunkMetadataList;
    }

   private:
    // ChunkMetadata for time column
    std::unique_ptr<IChunkMetadata> time_chunk_metadata_;
    // ChunkMetadata for all subSensors in the vector
    std::vector<std::unique_ptr<IChunkMetadata>> value_chunk_metadata_list_;
};

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