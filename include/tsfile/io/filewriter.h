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

#if 0
#ifndef IOTDB_NATIVE_WRITER_H
#define IOTDB_NATIVE_WRITER_H
#include <filesystem>
#include <optional>

#include "result.h"
#include "schema.h"
namespace iotdb::tsfile::io {
class TsRecord {
    uint64_t hashcode_;

   public:
    uint64_t hashcode() { return _hashcode; }
};
class Path {
    uint64_t _hashcode;

   public:
    uint64_t hashcode() { return _hashcode; }
};
enum class FileError {
    OK = 0,
    FORBIDDEN = 1,
    ERROR_WRITING = 2,
    ERROR_READING = 3,
    ERROR_SEEK = 4
};

class FileWriter {
   public:
    FileWriter(const std::filesystem::path file,
               const std::optional<schema>& schema = std::nullopt) {}
    StatusResult<FileError> Write(const record& item) {
        StatusResult<FileError> res(iotdb::tsfile::FileError::OK);
        return res;
    }
    StatusResult<FileError> Write(const record&& item) {
        StatusResult<FileError> res(iotdb::tsfile::FileError::OK);
        return res;
    }
    StatusResult<FileError> RegisterTimeSeries(const path& path, const measurement_schema& schema) {
        StatusResult<FileError> res(iotdb::tsfile::FileError::OK);
        return res;
    }
    StatusResult<FileError> register_device(const std::string& device_id,
                                            const std::string& template_name) {
        StatusResult<FileError> res(iotdb::tsfile::FileError::OK);
        return res;
    }

    void flush_chunks() {}
    void close() {}
};
}  // namespace iotdb::tsfile::io
#endif
#endif
