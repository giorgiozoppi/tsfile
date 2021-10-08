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

#include "tsfile/model/chunk_header.h"

namespace tsfile {

ChunkHeader::ChunkHeader(const std::string& measurementID, int dataSize, TsDataType dataType,
                         TsCompressionType compressionType, TsEncoding encoding, int numOfPages)
    : measurement_id_(measurementID),
      data_size_(dataSize),
      datatype_(dataType),
      compression_type_(compressionType),
      encoding_type_(encoding),
      num_of_pages_(numOfPages) {}

std::string ChunkHeader::MeasurementId() const noexcept { return measurement_id_; }

size_t ChunkHeader::DataSize() const noexcept { return data_size_; }

void ChunkHeader::SetMeasurementId(const std::string& id) noexcept { measurement_id_ = id; }

TsCompressionType ChunkHeader::CompressionType() const noexcept { return compression_type_; }

void ChunkHeader::SetCompressionType(const TsCompressionType& type) noexcept {
    compression_type_ = type;
}

TsDataType ChunkHeader::DataType() const noexcept { return datatype_; }

void ChunkHeader::SetDataType(const TsDataType& type) noexcept { datatype_ = type; }

TsEncoding ChunkHeader::Encoding() const noexcept { return encoding_type_; }

void ChunkHeader::SetEncoding(const TsEncoding& type) noexcept { encoding_type_ = type; }

int ChunkHeader::NumOfPages() const noexcept { return num_of_pages_; }

void ChunkHeader::SetNumOfPages(const int& num_of_pages) noexcept { num_of_pages_ = num_of_pages; }

uint64_t ChunkHeader::HashCode() const { return hashcode_; }

}  // namespace tsfile
