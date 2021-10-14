
#include "catch2/catch.hpp"
#include "tsfile/common/algorithm.h"
#include "tsfile/model/chunk.h"
#include "tsfile/model/chunk_group.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/datatypes.h"
#include "tsfile/model/statistics.h"
#include "tsfile/model/utility.h"
namespace tsfile {
SCENARIO("We can work correctly with a chunkgroup", "[model]") {
    GIVEN("a chunk group") {
        ChunkGroupFooter footer{"ShipThermometer", 1000, 10};
        auto group = std::make_unique<tsfile::ChunkGroup>(footer, kChunkGroupFooter);
        std::vector<Chunk> local_chunks;
        THEN("you can add chunks") {
            
            for (auto k = 0; k < 10; ++k) {
                const int kNumPages = 10;
                std::string measure{"Temperature"};
                tsfile::ChunkContext ctx{measure,
                                         10,
                                         tsfile::TsDataType::INT32,
                                         tsfile::TsCompressionType::GZIP,
                                         tsfile::TsEncoding::GORILLA,
                                         0,
                                         tsfile::kOnlyOnePageChunkHeader};
                auto chunk = tsfile::MakeChunk(ctx);
                auto sample_page = tsfile::MakePage(4096, 1024, tsfile::TsDataType::INT32);
                for (int i = 0; i < kNumPages; ++i) {
                    chunk.AddPage(MakePage(4096, 1024, TsDataType::INT32));
                    auto copy = chunk;
                    local_chunks.emplace_back(chunk);
                }
                group->AddChunk(std::move(chunk));
            }
            REQUIRE(group->GetSize() == 10);
        }
        THEN("you can remove chunks") {
        /*   group->RemoveChunk(local_chunks[0]);
           auto result = group->RemoveChunk(0);
           REQUIRE(result.HasValue() == true);
           REQUIRE(group->Size() == 8);
           */            
        }
        THEN("you can list all chunks both forward and backward") {}
        THEN("you can retrieve his footer") {}
    }
}
}  // namespace tsfile
