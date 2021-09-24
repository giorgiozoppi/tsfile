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
#ifndef IOTDB_NATIVE_TSFILEDEF_H
#define IOTDB_NATIVE_TSFILEDEF_H
#include <string>
namespace tsfile::common::constants {
const std::string TSFILE_SUFFIX{".tsfile"};
const std::string TSFILE_HOME{"TSFILE_HOME"};
const std::string PATH_ROOT{"root"};
const std::string TMP_SUFFIX{"tmp"};
const std::string PATH_SEPARATOR{"."};
const std::string PATH_SEPARATER_NO_REGEX{"\\."};
const std::string DOUBLE_QUOTE{'"'};
constexpr std::byte TIME_COLUMN_MASK = static_cast<std::byte>(0x80);
constexpr std::byte VALUE_COLUMN_MASK = static_cast<std::byte>(0x80);

}  // namespace tsfile::common::constants
#endif
