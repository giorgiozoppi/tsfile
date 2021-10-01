#ifndef IOTDB_NATIVE_MODEL_COMMON_H
#define IOTDB_NATIVE_MODEL_COMMON_H

#include <string>

#include "tsfile/common/common.h"
#include "tsfile/model/chunk.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/datatypes.h"

using iotdb::tsfile::common::Byte;

namespace iotdb::tsfile {

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
inline iotdb::tsfile::Chunk MakeChunk(const ChunkContext& context) {
    iotdb::tsfile::ChunkHeader temp_chunk_header{context.MeasurementID, context.DataSize,
                                                 context.DataType,      context.CompressionType,
                                                 context.Encoding,      context.NumberOfPages};

    return iotdb::tsfile::Chunk(std::move(temp_chunk_header), context.ChunkMarker);
}

///
/// @brief Factory method for an exclusive ownership Chunk
///
inline std::unique_ptr<iotdb::tsfile::Chunk> MakeUniqueChunk(const ChunkContext& context) {
    return std::make_unique<iotdb::tsfile::Chunk>(MakeChunk(context));
}

/// @brief Factory method for the page
///
inline Page MakePage(int uncompressed_size, int compressed_size, TsDataType statistics_type) {
    PageHeader header{uncompressed_size, compressed_size, statistics_type};
    header.SetStatistics(std::make_unique<StatisticsMap>(statistics_type));
    Page tmp(std::move(header));

    return tmp;
}
#if 0



iotdb::tsfile::Chunk MakeChunk(const ChunkContext& context) {
        iotdb::tsfile::ChunkHeader temp_chunk_header{
            context.MeasurementID,
            context.DataSize, 
            context.DataType, 
            context.CompressionType,
            context.Encoding,
            context.NumberOfPages};

        return iotdb::tsfile::Chunk(std::move(temp_chunk_header), context.ChunkMarker); 
}


///
/// @brief Factory method for an shared ownership Chunk
///
inline std::shared_ptr<iotdb::tsfile::Chunk> MakeSharedChunk(const ChunkContext& context) {
    return std::make_shared<iotdb::tsfile::Chunk>(MakeChunk(context));
}

/// @brief Factory method for the page
///
inline std::unique_ptr<Page> MakeUniquePage(int uncompressed_size, 
                    int compressed_size,
                    TsDataType statistics_type) {
        PageHeader header{uncompressed_size, compressed_size, statistics_type};
        header.SetStatistics(std::make_unique<StatisticsMap>(statistics_type));
        Page tmp(std::move(header));
        return std::make_unique<Page>(tmp);
}
#endif
}  // namespace iotdb::tsfile
#endif