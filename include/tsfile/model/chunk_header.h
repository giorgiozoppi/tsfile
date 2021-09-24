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
#include <string>

#include "datatypes.h"
#include "markers.h"

namespace iotdb::tsfile {
/**
 * Class that holds the responsibility to model a chunk header
 */
class chunk_header {
   public:
    /**
     * Construct a chunk header
     * @param measurementID     id of measurement
     * @param dataSize          size of the data
     * @param dataType          type of the data
     * @param compressionType   type of compression
     * @param encoding          type of encoding
     * @param numOfPages        numeber of pages
     */
    explicit chunk_header(const std::string& measurementID, int dataSize, ts_datatype dataType,
                          compression_type compressionType, ts_encoding encoding, int numOfPages);

    /**
     * Get measurement identifier
     * @return the measurement id
     */
    std::string get_measurement_id() const;

    /**
     * Get the data size.
     */
    size_t get_data_size() const;

    /**
     * Set measurement identifier
     * @param id
     */
    void set_measurement_id(const std::string& id);

    /**
     * Get the compression type.
     * @return compression type
     */
    compression_type get_compression_type() const;

    /**
     * Set the compression type
     * @param type of the compression.
     */
    void set_compression_type(const compression_type& type);

    /**
     * Get the time series data type
     * @return time series data type
     */
    ts_datatype get_ts_datatype() const;

    /**
     * Set the time series data type
     */
    void set_ts_datatype(const ts_datatype& type);

    /**
     * Get the time series data type
     * @return time series encoding.
     */
    ts_encoding get_ts_encoding() const;

    /**
     * Set the time series encoding
     * @param type series encoding
     */
    void set_ts_encoding(const ts_encoding& type);

    /**
     * Get number of pages
     * @return current number of pages.
     */

    int get_num_of_pages() const;

    /**
     * Set the number of paging
     * @param num_of_pages
     */
    void set_num_of_pages(const int& num_of_pages);

    uint64_t hash_code() const;

   private:
    uint64_t compute_hash();
    /**
     * 1 means this chunk has more than one page, so each page has its own page statistic 5 means
     * this chunk has only one page, and this page has no page statistic
     *
     * <p>if the 8th bit of this byte is 1 means this chunk is a time chunk of one vector if the 7th
     * bit of this byte is 1 means this chunk is a value chunk of one vector
     */
    std::byte _chunkType;
    std::string _measurement_id;
    int _data_size;
    ts_datatype _datatype;
    compression_type _compression_type;
    ts_encoding _encoding_type;
    int _num_of_pages;
    uint64_t _hashcode;
};
}  // namespace iotdb::tsfile
#endif  // IOTDB_NATIVE_CHUNK_HEADER_H
