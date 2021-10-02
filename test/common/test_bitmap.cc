#include <tsfile/common/bitmap.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "catch2/catch.hpp"



namespace tsfile {

constexpr int kBitMapSize = 256;

SCENARIO("Should check boundaries", "[bytebuffer]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap map{kBitMapSize};
        WHEN("we ask to set the bit 300") {
            auto result = map.Mark(300);
            THEN("we get out of range error") { REQUIRE(BitError::OUT_RANGE == result.Result()); }
        }
    }
}
SCENARIO("Should be able to set the bit correctly", "[bytebuffer]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap map{kBitMapSize};
        WHEN("we ask to set the bit 300") {
            auto result = map.Mark(200);
            THEN("we get out of range error") { REQUIRE(BitError::OK == result.Result()); }
        }
    }
}
SCENARIO("Should be able to mark all bits", "[bytebuffer]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap map{kBitMapSize};
        WHEN("we ask to set to mark all") {
            auto result = map.MarkAll();
            THEN("we get out of range error") {
                REQUIRE(BitError::OK == result.Result());
                for (size_t k = 0; k < kBitMapSize; ++k) {
                    auto v = map[k];
                    REQUIRE(1 == v.Value());
                }
            }
        }
    }
}
SCENARIO("Should be able to mark and unmark all bits", "[bytebuffer]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap map{kBitMapSize};
        WHEN("we ask to set to mark all") {
            auto result = map.MarkAll();
            auto other_result = map.Reset();
            THEN("we get out of range error") {
                BitMap clean{kBitMapSize};
                REQUIRE(BitError::OK == result.Result());
                REQUIRE(BitError::OK == other_result.Result());
                REQUIRE(map == clean);
            }
        }
        WHEN("we ask to mark and reset") {
            map.MarkAll();
            map.Reset();
            THEN("we get zero value at an arbitrary given bit") {
                REQUIRE(0 == map[10].Value());
            }
        }
    }
}

SCENARIO("Should be able to get the bit correctly", "[bytebuffer]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap map{kBitMapSize};
        WHEN("we ask to get/set several bits") {
            map.Mark(200);
            auto result = map[200];
            map.Mark(100);
            auto result1 = map[100];
            THEN("we get the correct values") {
                REQUIRE(BitError::OK == result.Result());
                REQUIRE(1 == result.Value());
                REQUIRE(1 == result1.Value());
            }
        }
    }
}
}  // namespace iotdb::tsfile::test
