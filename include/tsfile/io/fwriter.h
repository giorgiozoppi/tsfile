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

#ifndef IOTDB_NATIVE_WRITER_H
#define IOTDB_NATIVE_WRITER_H
#include <optional>

#include "result.h"
#include "schema.h"
namespace iotdb::tsfile::io {
class record {
    uint64_t _hashcode;

   public:
    uint64_t hashcode() { return _hashcode; }
};
class path {
    uint64_t _hashcode;

   public:
    uint64_t hashcode() { return _hashcode; }
};

class file_writer {
   public:
    file_writer(const std::filesystem::path file,
                const std::optional<schema>& schema = std::nullopt) {}
    result<io_status> write(const record&) {
        result<io_status> res(iotdb::tsfile::io_status::OK);
        return res;
    }
    result<io_status> write(const record&&) {
        result<io_status> res(iotdb::tsfile::io_status::OK);
        return res;
    }
    result<io_status> register_timeseries(const path& path, const measurement_schema& schema) {
        result<io_status> res(iotdb::tsfile::io_status::OK);
        return res;
    }
    result<io_status> register_device(const std::string& device_id,
                                      const std::string& template_name) {
        result<io_status> res(iotdb::tsfile::io_status::OK);
        return res;
    }
    void flush_chunks() {}
    void close() {}
};
}  // namespace iotdb::tsfile::io
#endif
