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
#include <tsfile/common/common.h>
#include <tsfile/model/chunk_group.h>
#include <tsfile/model/metadata.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>

namespace tsfile {
///
/// @brief Represent the structure of a IOTDB TSFile in memory.
///
class TsFile {
   public:
    static constexpr unsigned short kVersionSize = 6;

    ///
    /// @brief Supported version for the IOTDB TSFile.
    ///
    const std::array<Byte, kVersionSize> Version() const { return version_number_; }
    ///
    /// @brief MagicString for the IOTDB TSFile
    ///
    const std::string MagicString() const { return magic_string_; }

   private:
    std::array<Byte, kVersionSize> version_number_;
    std::string magic_string_;
    std::unique_ptr<ChunkGroup> chunks_;
    std::unique_ptr<TsFileMetadata> metadata_;
};
}  // namespace tsfile

#endif  // TSFILE_TSFILE_H
