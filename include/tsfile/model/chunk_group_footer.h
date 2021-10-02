/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
#define IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
#include <string>
#include <string_view>

namespace tsfile {
//
// @brief  ChunkGroupFooter. Each ChunkGroup in a TsFile has a footer.
//
class ChunkGroupFooter {
   public:
    ///
    /// @brief Construct a new chunk group footer object
    ///
    /// @param device_id        device identifier
    /// @param data_size        data dimension
    /// @param number_of_chunks number of chunks
    ///
    ChunkGroupFooter(const std::string_view& device_id, int64_t data_size, int number_of_chunks);
    ///
    /// @brief Get the device id object
    ///
    /// @return std::string
    ///
    std::string DeviceId() const;
    ///
    /// @brief Get the data size object
    ///
    /// @return Data dimension
    ///
    int64_t DataSize() const;
    ///
    /// @brief Get the number of chunks object
    ///
    /// @return number of chunks
    ///
    int NumberOfChunks() const;

   private:
    std::string device_id_;
    long data_size_;
    int number_of_chunks_;
};
}  // namespace tsfile
#endif  // IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
