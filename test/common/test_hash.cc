#include <tsfile/common/hash.h>

#include <functional>
#include <tuple>

#include "catch2/catch.hpp"
#if 0
namespace tsfile {
SCENARIO("We should be able to compute all hash functions correctly", "[model]") {
    GIVEN("A bytebuffer with a well know bitset") {
        ByteBuffer buffer{0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
        WHEN("ask to perform the murmur3 hash") {
            auto result = tsfile::ByteMurmurHash3{}(buffer);
            THEN("we get the expected result") { REQUIRE("" == result.Hex()); }
        }
        WHEN("ask to perform the sip hash function") {
            auto result = tsfile::ByteSipHash{}(buffer);
            THEN("we get the expected result") { REQUIRE("" == result.Hex()); }
        }
    }
    
    GIVEN("A serializable object, with several simple members") {
        struct SimpleDataObject {
            std::string id{"1291829HYYU"};
            uint32_t age{1912};
            float area{1.23};
            double pi{3.14159129};
            auto Members() { return std::forward_as_tuple(id, age, area, pi); }
        };
        SimpleDataObject dataObject;
        WHEN("i pass that to an object hasher") {
            THEN("i get the right hash") { auto value = ObjectHasher{dataObject}();
                std::cout << value << std::endl;
            }
        }
    }
    
}

}  // namespace tsfile
#endif
