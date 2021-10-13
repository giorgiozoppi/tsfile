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
#include "tsfile/common/algorithm.h"
#include "tsfile/model/chunk.h"
#include "tsfile/model/chunk_header.h"
#include "tsfile/model/datatypes.h"
#include "tsfile/model/statistics.h"
#include "tsfile/model/utility.h"
#include "tsfile/model/metadata.h"

namespace tsfile {

SCENARIO("MetadataIndex should behave like a real index", "[model]") {
    GIVEN("a metadata index") {
        auto index = std::make_unique<MetadataIndexNode>(MetadataIndexNodeType::INTERNAL_DEVICE);

        WHEN("you add 5 entities with 5 measurements each") {
            THEN("We should be able to search for an element") {}
        }
        WHEN("you add 1 entity with 150 measurements") {
            THEN("We should be able to search for an element") {}
        }
        WHEN("you add 150 entities with 10 measurement each") {
            THEN("We should be able to search for an element") {}
        }
        WHEN("you add 150 entities with 150 measurements each") {
            THEN("We should be able to search for an element") {}
        }
        WHEN("you add 1 entities with 2 vectors, 9 measurements for each vector") {
            THEN("We should be able to search for an element") {}
            THEN("We should update add another vector and find the added value") {}
        }
        WHEN("you add 1 entities with 10 vectors, 9 measurements for each vector") {
            THEN("We should be able to search for an element") {}
            THEN("We should clean the index without leaks") {}
            THEN("Only one INTERNAL_IDENTITY should be present") {}
        }
    }
}
}  // namespace tsfile