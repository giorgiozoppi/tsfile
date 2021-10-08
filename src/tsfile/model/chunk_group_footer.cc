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
#include "tsfile/model/chunk_group_footer.h"

namespace tsfile {
std::string ChunkGroupFooter::DeviceId() const { return device_id_; }
size_t ChunkGroupFooter::DataSize() const { return data_size_; }
int ChunkGroupFooter::NumberOfChunks() const { return number_of_chunks_; }
}  // namespace tsfile