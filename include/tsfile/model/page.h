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

#ifndef IOTDB_NATIVE_PAGE_H
#define IOTDB_NATIVE_PAGE_H
#include "page_header.h"
namespace iotdb::tsfile {

class page {
    page_header page_header_;
    long hash_code_{0};

   public:
    page(const page_header& header) : page_header_(header) {}
    page(page_header&& header);

    // comparision between chunks
    bool operator==(const page& source) const noexcept;
    bool operator<(const page& source) const noexcept;
    bool operator<=(const page& source) const noexcept;
    bool operator>(const page& source) const noexcept;
    bool operator>=(const page& source) const noexcept;
    void set_header(page_header&& header);
    page_header header() const;
    long hash_code() const;
};
}  // namespace iotdb::tsfile
#endif