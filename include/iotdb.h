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
#ifndef IOTDB__H
#define IOTDB__H

#include <stdint.h>
#include <vector>

#include <tsfile/encoding/endian_type.h>

namespace iotdb {
    typedef char value_type;
    typedef std::vector<value_type> container_type;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    constexpr tsfile::encoding::endian_type byte_order = tsfile::encoding::endian_type::IOTDB_LITTLE_ENDIAN;
#else
    constexpr tsfile::encoding::endian_type byte_order = tsfile::encoding::endian_type::IOTDB_BIG_ENDIAN;
#endif
}

#endif // IOTDB__H
