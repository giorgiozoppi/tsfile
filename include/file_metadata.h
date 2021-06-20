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
#ifndef IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H
#define IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H

#include <string>
#include <unordered_map>

#include <tsfile/file/metadata/device_metadata_index.h>
#include <tsfile/utils/bloom_filter.h>
#include <util/bitset.h>
#include <util/bytebuffer.h>
#include <util/rwio.h>
#include <write/schema/measurement_schema.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace metadata{
            using device_map = std::unordered_map<std::string, metadata::device_metadata_index>;
            using measurement_map = std::unordered_map<std::string, metadata::measurement_schema>;

            class file_metadata {
                device_map _device_map;
                measurement_map _measurement_map;
                std::string _created_by;
                int32_t _total_chunk_num;
                int32_t _invalid_chunk_num;
                utils::bloom_filter _bloom_filter;

            public:
                explicit file_metadata(device_map device_map, measurement_map measurement_map
                                       , std::string created_by, int32_t total_chunk_num
                                       , int32_t invalid_chunk_num, utils::bloom_filter bloom_filter)
                    : _device_map{device_map}, _measurement_map{measurement_map}, _created_by{created_by}
                    , _total_chunk_num{total_chunk_num}, _invalid_chunk_num{invalid_chunk_num}
                    , _bloom_filter{bloom_filter}
                {}
            };

            device_map make_device_map(util::buffer_window& buf) {
                device_map m;
                int32_t size = rwio::read<int32_t>(buf).value();
                if (size > 0) {
                    for (int i = 0; i < size; ++i) {
                        std::string key = rwio::read<std::string>(buf).value_or("");
                        metadata::device_metadata_index value(buf);
                        m.insert({key, value});
                    }
                }
                return m;
            }

            measurement_map make_measurement_map(util::buffer_window& buf) {
                measurement_map m;
                int32_t size = rwio::read<int32_t>(buf).value();
                if (size > 0) {
                    for (int i = 0; i < size; ++i) {
                        std::string key = rwio::read<std::string>(buf).value_or("");
                        metadata::measurement_schema value(buf);
                        m.insert({key, value});
                    }
                }
                return m;
            }

            file_metadata make_file_metadata(util::buffer_window& buf) {
                device_map device_map = make_device_map(buf);
                measurement_map measurement_map = make_measurement_map(buf);
                std::string created_by;
                int32_t total_chunk_num;
                int32_t invalid_chunk_num;
                utils::bloom_filter bloom_filter;

                if (rwio::read<bool>(buf) == true) {
                    created_by = rwio::read<std::string>(buf).value_or("");
                }

                total_chunk_num = rwio::read<int32_t>(buf).value();
                invalid_chunk_num = rwio::read<int32_t>(buf).value();

                // read bloom filter
                if (buf.size() > 0) {
                    bloom_filter = utils::make_bloom_filter(buf);
                }

                return file_metadata{device_map, measurement_map, created_by
                            , total_chunk_num, invalid_chunk_num, bloom_filter};
            }

            }
        }
    }
}

#endif // IOTDB__TSFILE__FILE__METADATA__FILE_METADATA__H
