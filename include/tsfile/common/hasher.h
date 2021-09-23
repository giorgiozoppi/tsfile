/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#ifndef IOTDB_NATIVE_CHUNK_HASHER_H
#define IOTDB_NATIVE_CHUNK_HASHER_H
#include <cstdint>
#include <tuple>
#include <vector>

namespace iotdb::tsfile {
class hasher {
   public:
    void add(double data);
    void add(long data);
    void add(int data);
    void add(unsigned int data);
    void add(float data);
    void add(unsigned long data);
    void add(std::byte data);
    uint64_t compute();

   private:
    void add_data(uint64_t data, std::vector<uint8_t>& value);
    uint64_t gen_key_part();
    std::vector<uint8_t> _data;
};
}  // namespace iotdb::tsfile
#endif
