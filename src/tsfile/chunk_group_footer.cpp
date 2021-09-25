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

#include "model/chunk_group_footer.h"

namespace iotdb::tsfile {
chunk_group_footer::chunk_group_footer(const std::string_view& device_id, long data_size,
                                       int number_of_chunks)
    : _device_id(device_id), _data_size(data_size), _number_of_chunks(number_of_chunks) {}
std::string chunk_group_footer::get_device_id() const { return _device_id; }
long chunk_group_footer::get_data_size() const { return _data_size; }
int chunk_group_footer::get_number_of_chunks() const { return _number_of_chunks; }
}  // namespace iotdb::tsfile
