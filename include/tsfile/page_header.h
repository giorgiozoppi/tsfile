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

#ifndef IOTDB_NATIVE_PAGE_HEADER_H
#define IOTDB_NATIVE_PAGE_HEADER_H
#include <memory>
#include <vector>

#include "statistics.h"
namespace iotdb::tsfile {
using stat_iterator = std::vector<iotdb::tsfile::statistics>::iterator;
using reverse_stat_iterator = std::vector<iotdb::tsfile::statistics>::reverse_iterator;
using const_stat_iterator = std::vector<iotdb::tsfile::statistics>::const_iterator;
using const_reverse_stat_iterator = std::vector<iotdb::tsfile::statistics>::const_reverse_iterator;

class page_header {
    int uncompressed_size;
    int compressed_size;
    std::vector<iotdb::tsfile::statistics> _statistics;

   public:
    page_header(int uncompressed_size, int compressed_size);
    int uc_size() const;
    int c_size() const;
    void add_statistic(const iotdb::tsfile::statistics& statistics);
    bool remove_statistic(const iotdb::tsfile::statistics& statistics);
    stat_iterator begin();
    stat_iterator end();
    reverse_stat_iterator rbegin();
    reverse_stat_iterator rend();
    const_stat_iterator cbegin() const;
    const_stat_iterator cend() const;
    const_reverse_stat_iterator crbegin() const;
    const_reverse_stat_iterator crend() const;
};
}  // namespace iotdb::tsfile
#endif