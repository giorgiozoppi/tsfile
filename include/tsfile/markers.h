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
namespace iotdb::tsfile::file {
constexpr uint8_t CHUNK_GROUP_FOOTER = 0;
constexpr uint8_t CHUNK_HEADER = 1;
constexpr uint8_t SEPARATOR = 2;
constexpr uint8_t VERSION = 3;
}  // namespace iotdb::tsfile::file
#endif  // IOTDB_NATIVE_MARKERS_H
