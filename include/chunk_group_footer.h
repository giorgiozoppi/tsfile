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
#include <tsfile/file/markers.h>
#include <tsfile/file/footer/chunk_group_footer.h>
#include <util/bytebuffer.h>
namespace iotdb::tsfile::file {
            class chunk_group_footer {
            public:
                chunk_group_footer(const std::string &device_id, long data_size, int number_of_chunks);
                std::string get_device_id() const;
                int get_data_size() const;
                int get_number_of_chunks() const;
            private:
                std::string _device_id;
                long _data_size;
                int _number_of_chunks;
                int _serialized_size;
            };
}
#endif //IOTDB_NATIVE_CHUNK_GROUP_FOOTER_H
