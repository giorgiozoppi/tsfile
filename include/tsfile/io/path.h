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
#ifndef IOTDB_NATIVE_PATH_H
#define IOTDB_NATIVE_PATH_H
#include <filesystem>
#include <string>

namespace iotdb::tsfile::io {
class path {
   public:
    path(const std::string& device, const std::string& measure);
    uint64_t hash_code() const;
    //auto operator<=>(const path& source) const;
    std::filesystem::path fullpath() const;
    std::string measurement() const;
    void set_measurement(const std::string& path);
    std::string str() const;
    std::string device() const;
    void set_device(const std::string& device);
   private:
    uint64_t _hash_code;
    std::string _device;
    std::string _measurement;
    std::filesystem::path _fullpath;
};
}
#endif