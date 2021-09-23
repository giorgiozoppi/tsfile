#include "catch2/catch.hpp"
#include "tsfile/model/datatypes.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/chunk.h"

using iotdb::tsfile::chunk;
using iotdb::tsfile::chunk_header;
using iotdb::tsfile::compression_type;
using iotdb::tsfile::ts_datatype;
using iotdb::tsfile::ts_encoding;
using iotdb::tsfile::page_header;
using iotdb::tsfile::page;



SCENARIO("chunk should be initialized correctly", "[model]]") {
    GIVEN("a chunk with a header and a page") {
        chunk_header temp_chunk_header{"temperature", 10, ts_datatype::INT32, compression_type::GZIP, ts_encoding::GORILLA, 1};
        chunk temp_chunk{temp_chunk_header, iotdb::tsfile::ONLY_ONE_PAGE_CHUNK_HEADER};
        page_header temp_page_header{1024, 4096};
        page temp_page{temp_page_header};
        
        temp_chunk.add_page(std::move(temp_page));
        WHEN("we access to values") {
            THEN("the correct pages are accessed correctly") {
                int items{0};
                for (auto& t: temp_chunk) {
                    REQUIRE(1024 == t.header().c_size());
                    REQUIRE(2048 == t.header().uc_size());
                    items++;
                }
                // hash just one page.
                REQUIRE(1==items);
            }
            THEN("the chunk header values are correct") {
                auto headers = temp_chunk.header();
                REQUIRE(compression_type::GZIP == headers.get_compression_type());
                REQUIRE(ts_datatype::INT32 == headers.get_ts_datatype());
                REQUIRE(ts_encoding::GORILLA == headers.get_ts_encoding());
                REQUIRE(1 == headers.get_num_of_pages() );
                 
            }
        }
    }
}