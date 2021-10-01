#ifndef IOTDB_NATIVE_MODEL_COMMON_H
#define IOTDB_NATIVE_MODEL_COMMON_H

#include <string>

#include "tsfile/common/common.h"
#include "tsfile/model/chunk_group.h"

using iotdb::tsfile::common::Byte;

namespace iotdb::tsfile {

inline std::unique_ptr<ChunkGroup> make_unique_chunk_group(const std::string_view& device_id,
                                                           long data_size) {
    auto footer = ChunkGroupFooter(device_id, data_size, 0);
    return std::make_unique<ChunkGroup>(std::move(footer),
                                        iotdb::tsfile::common::CHUNK_GROUP_FOOTER);
}

///
/// @brief ChunkContext context for chunk creation
///
struct ChunkContext {
    std::string MeasurementID;
    int DataSize{0};
    TsDataType DataType{TsDataType::BINARY};
    TsCompressionType CompressionType{TsCompressionType::UNCOMPRESSED};
    TsEncoding Encoding{TsEncoding::PLAIN};
    int NumberOfPages{0};
    Byte ChunkMarker{0};
};

///
/// @brief Factory method for the chunk
///
inline iotdb::tsfile::Chunk make_chunk(const ChunkContext& context) {
    iotdb::tsfile::ChunkHeader temp_chunk_header{context.MeasurementID, context.DataSize,
                                                 context.DataType,      context.CompressionType,
                                                 context.Encoding,      context.NumberOfPages};

    return iotdb::tsfile::Chunk(std::move(temp_chunk_header), context.ChunkMarker);
}

///
/// @brief Factory method for an exclusive ownership Chunk
///
inline std::unique_ptr<iotdb::tsfile::Chunk> make_unique_chunk(const ChunkContext& context) {
    return std::make_unique<iotdb::tsfile::Chunk>(make_chunk(context));
}

/// @brief Factory method for the page
///
inline Page make_page(int uncompressed_size, int compressed_size, TsDataType statistics_type) {
    PageHeader header{uncompressed_size, compressed_size, statistics_type};
    header.SetStatistics(std::make_unique<StatisticsMap>(statistics_type));
    Page tmp(std::move(header));

    return tmp;
}

/// @brief Factory method for  an exclusive ownership Page
inline std::unique_ptr<Page> make_unique_page(int uncompressed_size, int compressed_size,
                                              TsDataType statistics_type) {
    PageHeader header{uncompressed_size, compressed_size, statistics_type};
    header.SetStatistics(std::make_unique<StatisticsMap>(statistics_type));
    Page tmp(std::move(header));
    return std::make_unique<Page>(tmp);
}

}  // namespace iotdb::tsfile
#endif