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
*/

#include <istream>
namespace iotdb::io {
typedef std::basic_ifstream<std::byte> ifbstream;
typedef std::basic_ofstream<std::byte> ofbstream;
typedef std::basic_istream<std::byte> ibstream;
typedef std::basic_ostream<std::byte> obstream;
constexpr int DEFAULT_BYTES_READ = 4096;
}  // namespace iotdb::io
