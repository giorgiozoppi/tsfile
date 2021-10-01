#ifndef IOTDB_NATIVE_MODEL_COMMON_H
#define IOTDB_NATIVE_MODEL_COMMON_H

#include "tsfile/common/common.h"
#include "tsfile/model/chunk.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/datatypes.h"
using iotdb::tsfile::common::Byte;

namespace iotdb::tsfile {

/// TsFile Markers
constexpr Byte CHUNK_GROUP_FOOTER = Byte{0};
constexpr Byte CHUNK_HEADER = Byte{1};
constexpr Byte SEPARATOR = Byte{2};
constexpr Byte VERSION = Byte{3};
constexpr Byte OPERATION_INDEX_RANGE = Byte{4};
constexpr Byte ONLY_ONE_PAGE_CHUNK_HEADER = Byte{5};

///
/// @brief ChunkContext context for chunk creation
///
struct ChunkContext {
    std::string MeasurementID;
    int DataSize;
    TsDataType DataType;
    TsCompressionType CompressionType;
    TsEncoding Encoding;
    int NumberOfPages;
    Byte ChunkMarker;
};
///
/// @brief Factory method for the chunk
///
inline Chunk MakeChunk(const ChunkContext& context) {
        ChunkHeader temp_chunk_header{
            context.MeasurementID,
            context.DataSize, 
            context.DataType, 
            context.CompressionType,
            context.Encoding,
            context.NumberOfPages};

        return Chunk(std::move(temp_chunk_header), context.ChunkMarker); 
}
///
/// @brief Factory method for an exclusive ownership Chunk
///
inline std::unique_ptr<Chunk> MakeUniqueChunk(const ChunkContext& context) {
    return std::make_unique<Chunk>(MakeChunk(context));
}
///
/// @brief Factory method for an shared ownership Chunk
///
inline std::shared_ptr<Chunk> MakeSharedChunk(const ChunkContext& context) {
    return std::make_shared<Chunk>(MakeChunk(context));
}
}
#endif