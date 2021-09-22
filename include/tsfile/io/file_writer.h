/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef IOTDB_NATIVE_WRITER_H
#define IOTDB_NATIVE_WRITER_H
#include <filesystem>
#include <optional>
#include "schema.h"
#include "result.h"
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

class file_writer  {
    public:
    file_writer(const std::filesystem::path file, const std::optional<schema>& schema = std::nullopt){}
    status_result<file_error> write(const record&) { 
        status_result<file_error> res(iotdb::tsfile::file_error::OK);
        return res;
    }
    status_result<file_error> write(const record&&) { 
        status_result<file_error> res(iotdb::tsfile::file_error::OK);
        return res;
    }
    status_result<file_error> register_timeseries(const path& path, const measurement_schema& schema) {
        status_result<file_error> res(iotdb::tsfile::file_error::OK);
        return res;
    }
    status_result<file_error> register_device(const std::string& device_id, const std::string& template_name){
        status_result<file_error> res(iotdb::tsfile::file_error::OK);
        return res;
    }
    void flush_chunks() {}
    void close() {}
};
}
#endif
