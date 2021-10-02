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

#ifndef IOTDB_NATIVE_PAGE_H
#define IOTDB_NATIVE_PAGE_H
#include <tsfile/common/common.h>
#include <tsfile/model/page_header.h>

#include <memory>
#include <vector>

namespace tsfile {
///
/// @brief A Page stores a sequence of timeseries.
/// It is the smallest unit in which a data block is deserialized.
/// It contains a PageHeader and the actual data (encoded time-value pairs).
///
class Page {
   public:
    ///
    /// @brief Constructor
    /// @param header  a page header
    ///
    Page(PageHeader&& header) { page_header_ = std::move(header); }
    ///
    /// @brief Page Header
    ///
    PageHeader Header() const { return std::move(page_header_); }
    ///
    /// @brief HashCode of the page
    ///
    uint64_t HashCode() const { return hash_code_; }

   private:
    long hash_code_{0};
    PageHeader page_header_;
};
}  // namespace tsfile
#endif