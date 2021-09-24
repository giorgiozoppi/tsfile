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
#include "tsfile/io/path.h"

#include <string>

namespace iotdb::tsfile::io {
path::path(const std::string& device, const std::string& measure): _device(device), _measurement(measure) {}

uint64_t path::hash_code() const { return _hash_code; }
std::filesystem::path path::fullpath() const {
    return _fullpath;
}
std::string path::device() const { return _device; }

std::string path::str() const { return _fullpath.c_str();}
std::string path::measurement() const { return _measurement; }
void path::set_measurement(const std::string& measure) { _measurement = measure; }
}  // namespace iotdb::tsfile::io
