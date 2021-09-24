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
#include <filesystem>
#include <fstream>
#include <iostream>

#include "catch2/catch.hpp"
#include "common/bytebuffer.h"

using iotdb::common::bytebuffer;

SCENARIO("bytebuffer should be initialized correctly", "[chunk]") {
 
    GIVEN("a bytebuffer with predefined values") {
        bytebuffer buffer{1, 25, 32};
        WHEN("we access to values by index") {
            THEN("the correct values are accessed correctly") {
                REQUIRE(static_cast<char>(1) == buffer[0]);
                REQUIRE(static_cast<char>(25) == buffer[1]);
                REQUIRE(static_cast<char>(32) == buffer[2]);
            }
        }
    }
}
SCENARIO(" Assuring capacity of the buffer", "[bytebuffer]") {
    GIVEN("a bytebuffer with predefined size ") {
        bytebuffer buffer(10);
        WHEN("we ask to ensure the size") {
            THEN(" we double the capacity") {
                size_t capacity = buffer.capacity();
                buffer.ensure_space();
                REQUIRE(capacity * 2 == buffer.capacity());
            }
        }
    }
}
SCENARIO("Iterating a bytebuffer should work", "[bytebuffer]") {
    bytebuffer buffer{1, 2, 3, 4, 7, 8};
    WHEN("we loop through the byte buffer") {
        THEN(" the iteration is performed correctly") {
            int sum{0};
            const int matched{25};
            for (auto data : buffer) {
                sum += data;
            }
            REQUIRE(matched == sum);
        }
    }
}
SCENARIO("We should be able to (un)marshall correctly a byte buffer") {
    bytebuffer buffer{1, 2, 3, 4, 7, 8};
    std::filesystem::path tmp_file{"/tmp/buffer"};
    WHEN("we serialize a bytebuffer to a temporary file") {
        std::ofstream output_file{tmp_file};
        if (output_file.is_open()) {
            output_file << buffer;
            output_file.close();
        }
        THEN("we are able to read the same data") {
            std::ifstream in_file{tmp_file};
            bytebuffer tmp_buffer;
            in_file >> tmp_buffer;
            REQUIRE(buffer == tmp_buffer);
        }
    }
}
SCENARIO("We should be able to write and read correctly in a byte buffer") {
    bytebuffer buffer(10);
    WHEN(" assign bytes to the byte buffer") {
        THEN("then bytes are in the correct position in the array") {
            for (int i = 0; i < 3; i++) {
                buffer[i] = static_cast<char>(i);
            }
            REQUIRE(static_cast<char>(0) == buffer[0]);
            REQUIRE(static_cast<char>(1) == buffer[1]);
            REQUIRE(static_cast<char>(2) == buffer[2]);
        }
        THEN("i can use the iterators") {
            auto j = 0;
            for (char v : buffer) {
                REQUIRE(static_cast<char>(j) == v);
                j++;
            }
        }
    }
}