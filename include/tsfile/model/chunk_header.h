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

#ifndef IOTDB_NATIVE_CHUNK_HEADER_H
#define IOTDB_NATIVE_CHUNK_HEADER_H
#include <tsfile/model/datatypes.h>
#include <tsfile/model/markers.h>

#include <string>
namespace iotdb::tsfile {
///
/// @brief Class that holds the responsibility to model a chunk header
///
class ChunkHeader {
   public:
    ///
    /// @brief Construct a chunk header
    /// @param measurementID     id of measurement
    /// @param dataSize          size of the data
    /// @param dataType          type of the data
    /// @param compressionType   type of compression
    /// @param encoding          type of encoding
    /// @param numOfPages        numeber of pages
    ///
    explicit ChunkHeader(const std::string& measurementID, int dataSize, TsDataType dataType,
                         TsCompressionType compressionType, TsEncoding encoding, int numOfPages);
    ///
    /// @brief Get measurement identifier
    /// @return the measurement id
    ///
    std::string MeasurementId() const;
    ///
    /// @brief Get the data size.
    ///
    size_t DataSize() const;

    ///
    /// @brief Mark measurement identifier
    /// @param id Identifier of the measurement
    ///
    void SetMeasurementId(const std::string& id);

    ///
    /// @brief Get the compression type.
    /// @return compression type
    ///
    TsCompressionType GetCompressionType() const;

    ///
    /// Mark the compression type
    /// @param type of the compression.
    ///
    void CompressionType(const TsCompressionType& type);

    ///
    /// @brief Get the time series data type
    /// @return time series data type
    ///
    TsDataType DataType() const;

    ///
    /// @brief Mark the time series data type
    /// @param type set the type.
    ///
    void SetDataType(const TsDataType& type);

    ///
    /// @brief Get the time series data type
    /// @return Time series encoding.
    ///
    TsEncoding Encoding() const;

    ///
    /// @brief Mark the time series encoding
    /// @param type  Set the series encoding
    ///
    void SetTsEncoding(const TsEncoding& type);

    ///
    /// @brief Get number of pages
    /// @return Current number of pages.
    ///
    int NumOfPages() const;

    ///
    /// Mark the number of paging
    /// @param num_of_pages
    ///
    void SetNumOfPages(const int& num_of_pages);

    /// Return object hashcode
    ///
    uint64_t HashCode() const;

   private:
    uint64_t ComputeHash();
    ///
    /// 1 means this chunk has more than one Page, so each Page has its own Page statistic 5 means
    /// this chunk has only one Page, and this Page has no Page statistic
    ///
    /// <p>if the 8th bit of this byte is 1 means this chunk is a time chunk of one vector if the
    /// 7th
    // bit of this byte is 1 means this chunk is a value chunk of one vector
    ///
    // TODO add chunk type
    std::string measurement_id_;
    int data_size_;
    TsDataType datatype_;
    TsCompressionType compression_type_;
    TsEncoding encoding_type_;
    int num_of_pages_;
    uint64_t hashcode_;
};
}  // namespace iotdb::tsfile
#endif  // IOTDB_NATIVE_CHUNK_HEADER_H
