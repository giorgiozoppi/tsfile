#include <tsfile/common/common.h>

#include "catch2/catch.hpp"

namespace tsfile {
struct Person {
    std::string name_;
    std::string surname_;
};
enum class DbResult { OK, BAD_QUERY, CONNECTION_FAILED };
Expected<DbResult, Person> GetRecordByName() {
    return Expected(DbResult::OK, Person{"Aron", "Ressler"});
}
Expected<DbResult, Person> GetRecord() { return Expected<DbResult, Person>(DbResult::BAD_QUERY); }
SCENARIO("Expected should give us correct value and results", "[expected]") {
    WHEN("we call a function and it a success") {
        auto success = GetRecordByName();
        THEN("the value should be present and the code error OK") {
            REQUIRE(true == IsOk(success.Result()));
            REQUIRE(true == success.HasValue());
            REQUIRE(success.Value().name_ == "Aron");
            REQUIRE(success.Value().surname_ == "Ressler");
        }
    }
    WHEN("we call a functiona and it fails") {
        THEN("the failure is present and the result code also") {
            auto failure = GetRecord();
            REQUIRE(false == IsOk(failure.Result()));
            REQUIRE(DbResult::BAD_QUERY == failure.Result());
        }
    }
}
}  // namespace tsfile
