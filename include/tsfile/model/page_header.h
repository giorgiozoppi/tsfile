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

#ifndef IOTDB_NATIVE_PAGE_HEADER_H
#define IOTDB_NATIVE_PAGE_HEADER_H
#include <tsfile/common/bytebuffer.h>
#include <tsfile/model/statistics.h>

#include <memory>
#include <vector>
namespace tsfile {

using unique_statistics_ptr = std::unique_ptr<StatisticsMap>;
///
/// @brief PageHeader defines the kind of infomation of the Page: Compressed Size, Uncompressed
/// Size, Page Statistics.
///
class PageHeader {
   public:
    ///
    /// @brief Constructor
    ///
    PageHeader() = default;

    /// @brief Constructor
    /// @param uncompressed_size  GetHeader uncompressed size
    /// @param compressed_size    GetHeader compressed size
    /// @param page_type          GetDataType of the header
    PageHeader(int uncompressed_size, int compressed_size, TsDataType page_type);
    ///
    /// @brief Move constructor
    ///
    PageHeader(const PageHeader& header);
    ///
    /// @brief Move assignement operator
    /// @param header Source page to copy
    ///
    PageHeader& operator=(const PageHeader& header);

    ///
    /// @brief Move assignment constructor
    /// @param header Source page to move
    ///
    PageHeader(PageHeader&& header) noexcept;
    ///
    /// @brief Move assignment operator
    /// @param header Source page to move
    ///

    PageHeader& operator=(PageHeader&& header) noexcept;
    ///
    /// @brief Destructor
    ///
    ~PageHeader() = default;
    ///
    /// @brief Get the size of the header uncompress
    ///
    int UncompressedSize() const;
    ///
    /// @brief Get the compressed size of the header
    ///
    int CompressedSize() const;
    ///
    /// @brief Set the statistics
    /// @param statistics Pointer to the statistics
    ///
    void SetStatistics(unique_statistics_ptr&& statistics) noexcept;
    ///
    /// @brief Get to the statistics
    ///
    unique_statistics_ptr Statistics() const;

    EXPOSE_MEMBERS(uncompressed_size_, compressed_size_, page_type_, stat_)
   private:
    int uncompressed_size_{0};
    int compressed_size_{0};
    TsDataType page_type_{TsDataType::INT32};
    unique_statistics_ptr stat_{nullptr};
};
}  // namespace tsfile
#endif