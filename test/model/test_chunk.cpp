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

#include "tsfile/model/chunk.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/datatypes.h"
#include "tsfile/model/statistics.h"
#include "tsfile/model/common.h"


using namespace iotdb::tsfile;

SCENARIO("chunk should be initialized correctly", "[model]]") {
    GIVEN("a chunk with a header and a page") {
        ChunkContext ctx{"temperature", 10, TsDataType::INT32, TsCompressionType::GZIP, 
        TsEncoding::GORILLA, 1, ONLY_ONE_PAGE_CHUNK_HEADER};
        ChunkHeader temp_chunk_header{
            "temperature", 10, TsDataType::INT32, TsCompressionType::GZIP, TsEncoding::GORILLA, 1};
        Chunk temp_chunk{temp_chunk_header, iotdb::tsfile::ONLY_ONE_PAGE_CHUNK_HEADER};
        PageHeader temp_page_header{4096, 1024};
        auto s = std::make_unique<StatisticsMap>(TsDataType::INT32);
        temp_page_header.SetStatistics(std::move(s));
        Page temp_page{std::move(temp_page_header)};
        temp_chunk.AddPage(std::move(temp_page));
        WHEN("we access to values") {
            THEN("the correct pages are accessed correctly") {
                int items{0};
                for (auto& t : temp_chunk) {
                    REQUIRE(1024 == t.header().c_size());
                    REQUIRE(4096 == t.header().uc_size());
                    items++;
                }
                // hash just one page.
                REQUIRE(1 == items);
            }
            THEN("the chunk header values are correct") {
                auto headers = temp_chunk.Header();
                REQUIRE(TsCompressionType::GZIP == headers.get_TsCompressionType());
                REQUIRE(TsDataType::INT32 == headers.get_ts_datatype());
                REQUIRE(TsEncoding::GORILLA == headers.get_TsEncoding());
                REQUIRE(1 == headers.get_num_of_pages());
            }
        }
    }
}
