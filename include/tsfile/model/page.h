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
#include <memory>
#include <vector>

#include <tsfile/common/common.h>
#include <tsfile/model/page_header.h>

namespace iotdb::tsfile {
class page {
    long _hash_code{0};
   // page_header _page_header;

   public:
   // page(page_header&& header) { _page_header = std::move(header); }
   // page_header header() const { return std::move(_page_header); }
    uint64_t hash_code() const { return _hash_code; }
};
}  // namespace iotdb::tsfile
#endif