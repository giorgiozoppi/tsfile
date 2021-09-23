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

#ifndef IOTDB_NATIVE_MARKERS_H
#define IOTDB_NATIVE_MARKERS_H
namespace iotdb::tsfile {
constexpr std::byte CHUNK_GROUP_FOOTER = std::byte{0};
constexpr std::byte CHUNK_HEADER = std::byte{1};
constexpr std::byte SEPARATOR = std::byte{2};
constexpr std::byte VERSION = std::byte{3};
constexpr std::byte OPERATION_INDEX_RANGE = std::byte{4};
constexpr std::byte ONLY_ONE_PAGE_CHUNK_HEADER = std::byte{5};
}  // namespace iotdb::tsfile::file
#endif  // IOTDB_NATIVE_MARKERS_H
