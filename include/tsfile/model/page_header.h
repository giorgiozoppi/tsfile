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
namespace iotdb::tsfile {
using unique_stat_ptr = std::unique_ptr<StatisticsMap>;

class PageHeader {
    int _uncompressed_size{0};
    int _compressed_size{0};
    TsDataType _page_type{TsDataType::INT32};
    unique_stat_ptr _stat{nullptr};

   public:
    PageHeader() = default;

    PageHeader(int uncompressed_size, int compressed_size);

    PageHeader(int uncompressed_size, int compressed_size, ts_datatype page_type)
        : _uncompressed_size(uncompressed_size),
          _compressed_size(compressed_size),
          _page_type(page_type) {}

    PageHeader(const PageHeader& header) {
        _uncompressed_size = header._uncompressed_size;
        _compressed_size = header._compressed_size;
        if (_stat != nullptr) {
            _stat = std::make_unique<StatisticsMap>(*(header._stat));
        }
    }
    PageHeader& operator=(const PageHeader& header) {
        if (this != &header) {
            _uncompressed_size = header._uncompressed_size;
            _compressed_size = header._compressed_size;
            _page_type = header._page_type;
            if (header._stat != nullptr) {
                _stat = std::make_unique<StatisticsMap>(*(header._stat));
            }
        }
        return *this;
    }
    PageHeader(iotdb::tsfile::PageHeader&& header) noexcept {
        if (this != &header) {
            _uncompressed_size = std::exchange(header._uncompressed_size, 0);
            _compressed_size = std::exchange(header._compressed_size, 0);
            _page_type = std::move(header._page_type);
            if (header._stat != nullptr) {
                _stat = std::move(header._stat);
            }
        }
    }
    PageHeader& operator=(iotdb::tsfile::PageHeader&& header) noexcept {
        if (this != &header) {
            _uncompressed_size = std::exchange(header._uncompressed_size, 0);
            _compressed_size = std::exchange(header._compressed_size, 0);
            _page_type = std::move(header._page_type);
            if (header._stat != nullptr) {
                _stat = std::move(header._stat);
            }
        }
        return *this;
    }
    ~PageHeader() = default;

    int uc_size() const { return _uncompressed_size; }
    int c_size() const { return _compressed_size; }
    void set_statistics(unique_stat_ptr&& statistics) noexcept { _stat = std::move(statistics); }
    unique_stat_ptr statistics() const {
        auto tmp = std::make_unique<StatisticsMap>(*_stat);
        return tmp;
    }
};
}  // namespace iotdb::tsfile
#endif