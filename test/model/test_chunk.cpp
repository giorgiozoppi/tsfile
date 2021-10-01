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

#include "catch2/catch.hpp"
#include "tsfile/model/datatypes.h"
#include "tsfile/model/statistics.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/chunk.h"
#include "tsfile/model/utility.h"




using namespace iotdb::tsfile;
using namespace iotdb::tsfile::common;



SCENARIO("Chunk should be initialized correctly", "[model]]") {
    GIVEN("A chunk with N pages") {
        const int NUM_PAGES = 10;
        std::string measure{"Temperature"};
        ChunkContext ctx{measure, 10, TsDataType::INT32, TsCompressionType::GZIP, 
        TsEncoding::GORILLA, 0, ONLY_ONE_PAGE_CHUNK_HEADER};
        auto chunk = MakeUniqueChunk(ctx);
        for (int i = 0; i < NUM_PAGES; ++i) {
            chunk->AddPage(MakePage(4096, 1024, TsDataType::INT32));
        }
        WHEN("we access to the chunk") {
            THEN("all pages are correctly set") {
                int items{0};
                for (auto& page : *chunk) {
                    auto page_header = page.Header(); 
                    REQUIRE(1024 == page_header.CompressedSize());
                    REQUIRE(4096 == page_header.UncompressedSize());
                    items++;
                }
                // hash just one page.
                REQUIRE(NUM_PAGES == items);
            }
            THEN("the chunk header values are correct") {
                ChunkHeader header = chunk->Header();
                REQUIRE(TsCompressionType::GZIP == header.CompressionType());
                REQUIRE(TsDataType::INT32 == header.DataType());
                REQUIRE(TsEncoding::GORILLA == header.Encoding());
                REQUIRE(NUM_PAGES == header.NumOfPages());
            }
        }
    }
}