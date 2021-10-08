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

#include <iterator>
#include <limits>
#if defined(_WIN32)
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif  //

#include <tsfile/common/bytebuffer.h>
#include <tsfile/common/hash.h>

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
SCENARIO("We should always store primitive data in big endian") {
    GIVEN("an empty bytebuffer") {
        ByteBuffer intBuffer;
        WHEN("We append an integer") {
            THEN("Its big endian value is correct") {
                intBuffer.Append(pack<int>(static_cast<int>(1000)));
                auto int_value = intBuffer[0];
                REQUIRE(1000 == int_value);
                intBuffer.Clear();
            }
        }
    }
}
#if 0
SCENARIO("We should always store primitive data in big endian") {
    GIVEN("an empty bytbuffer") {
        ByteBuffer buffer;
        WHEN("We append a short") {
            THEN("Its big endian value is correct") {
                buffer.Append(10);
                auto short_value = ntohl(buffer[0]);
                REQUIRE(10 == short_value);
                buffer.Clear();
            }
        }
        WHEN("We append an integer") {
            THEN("Its big endian value is correct") {
                buffer.Append(1000);
                auto int_value = ntohl(buffer[0]);
                REQUIRE(1000 == int_value);
                buffer.Clear();
            }
        }
               WHEN("We append an double") {
            THEN("Its big endian value is correct") {
                constexpr double max_double_value= 9828192891.12123;
                buffer.Append(max_double_value);
                char bytes[8];
                double out_double_value{0};
                std::memcpy(bytes, &buffer[0], 8);
                std::reverse(std::begin(bytes), std::end(bytes));
                std::memcpy(&out_double_value, bytes, 8);
                REQUIRE(out_double_value == max_double_value);
                buffer.Clear();
            }
        }


        WHEN("We append an float") {
            THEN("Its big endian value is correct") {
                float max_float_value{10.02f};
                buffer.Append(pack(max_float_value));
                char bytes_1[4];
                std::memcpy(bytes_1, &buffer[0], 4);
                std::reverse(std::begin(bytes_1), std::end(bytes_1));
                float out_float_value;
                std::memcpy(&out_float_value, bytes_1, 4);
                REQUIRE(out_float_value == max_float_value);
                buffer.Clear();
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
#endif
}  // namespace tsfile