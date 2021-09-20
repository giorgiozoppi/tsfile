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

#ifndef IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
#define IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
#include <string>
namespace iotdb::tsfile {
/**
 * @brief  chunk group footer.
 *
 */
class chunk_group_footer {
   public:
    /**
     * @brief Construct a new chunk group footer object
     *
     * @param device_id
     * @param data_size
     * @param number_of_chunks
     */
    chunk_group_footer(const std::string& device_id, long data_size, int number_of_chunks);
    /**
     * @brief Get the device id object
     *
     * @return std::string
     */
    std::string get_device_id() const;
    /**
     * @brief Get the data size object
     *
     * @return long
     */
    long get_data_size() const;
    /**
     * @brief Get the number of chunks object
     *
     * @return int
     */
    int get_number_of_chunks() const;

   private:
    std::string _device_id;
    long _data_size;
    int _number_of_chunks;
};
}  // namespace iotdb::tsfile
#endif  // IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
