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
#ifndef IOTDB__TSFILE__FILE__METADATA__DEVICE_METADATA_INDEX__H
#define IOTDB__TSFILE__FILE__METADATA__DEVICE_METADATA_INDEX__H

#include <util/bytebuffer.h>
#include <util/rwio.h>

namespace rwio = iotdb::util::rwio;

namespace iotdb { namespace tsfile { namespace file { namespace metadata {

class device_metadata_index {
    int64_t _offset;
    int32_t _len;
    int64_t _start_time;
    int64_t _end_time;

public:
    explicit device_metadata_index(util::buffer_window& buf) {
        _offset = rwio::read<int64_t>(buf).value();
        _len = rwio::read<int32_t>(buf).value();
        _start_time = rwio::read<int64_t>(buf).value();
        _end_time = rwio::read<int64_t>(buf).value();
    }
};

}}}}

#endif // IOTDB__TSFILE__FILE__METADATA__DEVICE_METADATA_INDEX__H
