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
#include <memory>
#include <vector>

#include "common/bytebuffer.h"
#include "statistics.h"
namespace iotdb::tsfile {
using unique_stat_ptr = std::unique_ptr<stat_container>;

class page_header {
    int _uncompressed_size{0};
    int _compressed_size{0};
    ts_datatype _page_type{ts_datatype::INT32};
    unique_stat_ptr _stat{nullptr};

   public:
    page_header() = default;

    page_header(int uncompressed_size, int compressed_size)
        : _uncompressed_size(uncompressed_size), _compressed_size(compressed_size) {}

    page_header(int uncompressed_size, int compressed_size, ts_datatype page_type)
        : _uncompressed_size(uncompressed_size),
          _compressed_size(compressed_size),
          _page_type(page_type) {}

    page_header(const page_header& header) {
        _uncompressed_size = header._uncompressed_size;
        _compressed_size = header._compressed_size;
        if (_stat != nullptr) {
            _stat = std::make_unique<stat_container>(*(header._stat));
        }
    }
    page_header& operator=(const page_header& header) {
        if (this != &header) {
            _uncompressed_size = header._uncompressed_size;
            _compressed_size = header._compressed_size;
            _page_type = std::move(_page_type);
            if (_stat != nullptr) {
                _stat = std::make_unique<stat_container>(*(header._stat));
            }
        }
        return *this;
    }
    page_header(iotdb::tsfile::page_header&& header) {
        _uncompressed_size = std::move(header._uncompressed_size);
        _compressed_size = std::move(header._compressed_size);
        _page_type = std::move(_page_type);
        if (_stat != nullptr) {
            _stat = std::move(header._stat);
        }
    }
    ~page_header() = default;

    int uc_size() const { return _uncompressed_size; }
    int c_size() const { return _compressed_size; }
    void set_statistics(unique_stat_ptr&& statistics) { _stat = std::move(statistics); }
    unique_stat_ptr statistics() const {
        auto tmp = std::make_unique<stat_container>(*_stat);
        return tmp;
    }
};
}  // namespace iotdb::tsfile
#endif