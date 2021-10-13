#include <tsfile/common/algorithm.h>

#include <algorithm>
#include <functional>
#include <iostream>

#include "catch2/catch.hpp"

namespace tsfile {
struct Person {
    std::string first_name;
    std::string last_name;
    mutable std::size_t hash_code_;
    uint64_t HashCode() const {
        std::size_t h1 = std::hash<std::string>{}(first_name);
        std::size_t h2 = std::hash<std::string>{}(last_name);
        hash_code_ = h1 ^ (h2 << 1);
        return hash_code_;
    }
};

SCENARIO("We remove hashable datatype from a vectro", "[algorithm]") {
    GIVEN("a vector with K Hashable values") {
        constexpr auto kHashable = 10;
        std::vector<Person> person(kHashable);
        std::generate(begin(person), end(person), [] {
            Person p{"Gina", "Zanetakos", 0};
            //REQUIRE(10368218723229057486 == p.HashCode());
            return p;
        });
        REQUIRE(person.size() == kHashable);
        WHEN("we remove by hash the first") {
            auto killer = Person{"Gina", "Zanetakos", 0};
            THEN("we hava a vector with an element less") {
                REQUIRE(killer.first_name == "Gina");
                REQUIRE(killer.last_name == "Zanetakos");
                REQUIRE(true == EraseUsingHash(person, killer));
                REQUIRE(person.size() == 0);
            }
        }
        WHEN("we clear and remove an element") {
            person.clear();
            auto killer = Person{"Gina", "Zanetakos", 0};
            THEN("we have a failure") { REQUIRE(false == EraseUsingHash(person, killer)); }
        }
    }
}
}  // namespace tsfile