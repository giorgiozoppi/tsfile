#include <tsfile/common/bitmap.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "catch2/catch.hpp"

namespace tsfile {

constexpr int kBitMapSize = 256;

SCENARIO("Should creation and copy be fine", "[bitmap]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap m{256};
        WHEN("we mark 200th bit and copy") {
            m.Mark(200);
            BitMap k(m);
            BitMap f{1};
            f = m;
            THEN("the copy shall be have the same bit set") {
                REQUIRE(k[200].Value() == 1);
                REQUIRE(f[200].Value() == 1);
            }
            WHEN("we mark the 100th bit and move") {
                THEN("the transferred ownership is respected") {
                    m.Reset();
                    m.Mark(100);
                    BitMap g = std::move(m);
                    BitMap h{1};
                    REQUIRE(g[100].Value() == 1);
                    h = g;
                    REQUIRE(h[100].Value() == 1);
                    m = std::move(h);
                    REQUIRE(m[100].Value() == 1);
                    
                }
            }
        }
    }
}
SCENARIO("Should check boundaries", "[bitmap]") {
    GIVEN("A bytebuffer with predefined size of 256 bits") {
        BitMap map{kBitMapSize};
        WHEN("we ask to set the bit 300") {
            auto result = map.Mark(300);
            THEN("we get out of range error") { REQUIRE(BitError::OUT_RANGE == result.Result()); }
        }
        WHEN("we ask to set the bit 200") {
            auto result = map.Mark(200);
            THEN("we get ok") { REQUIRE(BitError::OK == result.Result()); }
        }
    }
}
SCENARIO("Should be able to mark all bits", "[bitmap]") {
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
SCENARIO("Should be able to mark and unmark all bits", "[bitmap]") {
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
            THEN("we get zero value at an arbitrary given bit") { REQUIRE(0 == map[10].Value()); }
        }
    }
}

SCENARIO("Should be able to get the bit correctly", "[bitmap]") {
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
}  // namespace tsfile
