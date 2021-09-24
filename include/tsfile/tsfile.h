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

#ifndef IOTDB_NATIVE_TSFILE_H
#define IOTDB_NATIVE_TSFILE_H
#include <array>
#include <cstddef>
#include <string>
#include <memory>
#include "model/chunk_group.h"
#include "model/ts_index.h"


    namespace iotdb::tsfile {
    class tsfile {
        std::string _magic_string;
        std::byte _version_number[6];
        std::unique_ptr<iotdb::tsfile::chunk_group> _chunks;
        std::unique_ptr<iotdb::tsfile::chunk_index> _chunk_index;
        std::unique_ptr<iotdb::tsfile::time_series_index> _ts_index;
        std::unique_ptr<iotdb::tsfile::secondary_index> _secondary_index;
       public:
        const std::array<std::byte, 6> version() const { return _version_number; }
        const std::string magic_string() const { return _magic_string; }
    };
}

#endif  // TSFILE_TSFILE_H
