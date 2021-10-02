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

#include <tsfile/common/bytebuffer.h>

#include "catch2/catch.hpp"

namespace tsfile {

SCENARIO("We should copy and get a hex representation", "[byetbuffer]") {
    GIVEN("a bytebuffer with predefined values") {
        ByteBuffer buffer{1, 25, 32};
        WHEN("coverting to hex") {
            THEN("we get the right results") {
                auto s = buffer.Hex();
                REQUIRE("011920" == s);
            }
        }
        WHEN("copy the value") {
            THEN("we get the hex right results") {
                auto s = buffer;
                auto first_hex_value = s.Hex();
                REQUIRE("011920" == first_hex_value);
            }
        }
    }
}

SCENARIO("bytebuffer should be initialized correctly", "[bytebuffer]") {
    GIVEN("a bytebuffer with predefined values") {
        ByteBuffer buffer{1, 25, 32};
        WHEN("we access to values by index") {
            THEN("the correct values are accessed correctly") {
                REQUIRE(static_cast<Byte>(1) == buffer[0]);
                REQUIRE(static_cast<Byte>(25) == buffer[1]);
                REQUIRE(static_cast<Byte>(32) == buffer[2]);
            }
        }
    }
}
SCENARIO("Iterating a bytebuffer should work", "[bytebuffer]") {
    ByteBuffer buffer{1, 2, 3, 4, 7, 8};
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
SCENARIO("Reverse iterating a bytebuffer should work", "[bytebuffer]") {
    ByteBuffer buffer{3, 4, 5, 6, 7, 8};
    WHEN("we loop backward through the byte buffer") {
        THEN(" the iteration is performed correctly") {
            int last{8};
            for (auto i = buffer.rbegin(); i != buffer.rend(); i++) {
            
                REQUIRE(*i == last);
                last--;
            }
        }
    }
}
SCENARIO("We should be able to write and read correctly in a byte buffer") {
    ByteBuffer buffer;
    WHEN(" We assign bytes to the byte buffer") {
        THEN("bytes are in the correct position in the array") {
            for (int i = 0; i < 3; i++) {
                buffer.Add(static_cast<Byte>(i));
            }
            REQUIRE(static_cast<Byte>(0) == buffer[0]);
            REQUIRE(static_cast<Byte>(1) == buffer[1]);
            REQUIRE(static_cast<Byte>(2) == buffer[2]);
        }
        THEN("i can use the iterators") {
            char j = 0;

            for (auto v : buffer) {
                REQUIRE(j == v);
                j++;
            }
        }
    }
}
}  // namespace tsfile