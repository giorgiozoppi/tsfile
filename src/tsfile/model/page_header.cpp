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

#include <tsfile/model/page_header.h>

namespace iotdb::tsfile {

PageHeader::PageHeader() = default;

PageHeader::PageHeader(int uncompressed_size, int compressed_size, TsDataType page_type)
    : uncompressed_size_(uncompressed_size),
      compressed_size_(compressed_size),
      page_type_(page_type) {}

PageHeader::PageHeader(const PageHeader& header) {
    uncompressed_size_ = header.uncompressed_size_;
    compressed_size_ = header.compressed_size_;
    if (stat_ != nullptr) {
        stat_ = std::make_unique<StatisticsMap>(*(header.stat_));
    }
}

PageHeader& PageHeader::operator=(const PageHeader& header) {
    if (this != &header) {
        uncompressed_size_ = header.uncompressed_size_;
        compressed_size_ = header.compressed_size_;
        page_type_ = header.page_type_;
        if (header.stat_ != nullptr) {
            stat_ = std::make_unique<StatisticsMap>(*(header.stat_));
        }
    }
    return *this;
}

PageHeader::PageHeader(PageHeader&& header) noexcept {
    if (this != &header) {
        uncompressed_size_ = std::exchange(header.uncompressed_size_, 0);
        compressed_size_ = std::exchange(header.compressed_size_, 0);
        page_type_ = std::move(header.page_type_);
        if (header.stat_ != nullptr) {
            stat_ = std::move(header.stat_);
        }
    }
}

PageHeader& PageHeader::operator=(PageHeader&& header) noexcept {
    if (this != &header) {
        uncompressed_size_ = std::exchange(header.uncompressed_size_, 0);
        compressed_size_ = std::exchange(header.compressed_size_, 0);
        page_type_ = std::move(header.page_type_);
        if (header.stat_ != nullptr) {
            stat_ = std::move(header.stat_);
        }
    }
    return *this;
}

int PageHeader::UncompressedSize() const { return uncompressed_size_; }

int PageHeader::CompressedSize() const { return compressed_size_; }

void PageHeader::SetStatistics(UniqueStatisticsPtr&& statistics) noexcept {
    stat_ = std::move(statistics);
}

UniqueStatisticsPtr PageHeader::Statistics() const {
    auto tmp = std::make_unique<StatisticsMap>(*stat_);
    return tmp;
}
}  // namespace iotdb::tsfile