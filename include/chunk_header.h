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

#ifndef IOTDB_NATIVE_CHUNK_HEADER_H
#define IOTDB_NATIVE_CHUNK_HEADER_H

#include <iostream>
#include <util/rwio.h>
#include <tsfile/file/metadata/metadata.h>
#include <tsfile/file/markers.h>


namespace iotdb::tsfile::file {

                namespace rwio = iotdb::util::rwio;

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
                    explicit chunk_header(const std::string& measurementID,int dataSize,
                                ts_datatype dataType,
                                compression_type compressionType,
                                ts_encoding encoding,
                                int numOfPages);
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
                    void set_measurement_id(const std::string &id);

                    /**
                     * Get the compression type.
                     * @return compression type
                     */
                    compression_type get_compression_type() const;
                    /**
                     * Set the compression type
                     * @param type of the compression.
                     */
                    void set_compression_type(const compression_type &type);
                    /**
                     * Get the time series data type
                     * @return time series data type
                     */
                    ts_datatype get_ts_datatype() const;
                    /**
                     * Set the time series data type
                     */
                    void set_ts_datatype(const ts_datatype &type);
                    /**
                     * Get the time series data type
                     * @return time series encoding.
                     */
                    ts_encoding get_ts_encoding() const;
                    /**
                     * Set the time series encoding
                     * @param type series encoding
                     */
                    void set_ts_encoding(const ts_encoding &type);
                    /**
                     * Get number of pages
                     * @return current number of pages.
                     */

                    int get_num_of_pages() const;
                    /**
                     * Set the number of paging
                     * @param num_of_pages
                     */
                    void set_num_of_pages(const int &num_of_pages);
                    /**
                     *
                     * @return
                     */
                    std::string str() const;

                private:
                    std::string _measurement_id;
                    int _data_size;
                    ts_datatype _datatype;
                    compression_type _compression_type;
                    ts_encoding _encoding_type;
                    int _num_of_pages;
                };
    
                /**
                 * Create a header from a stream or a buffer.
                 * @tparam T  stream or buffer to be used.
                 * @param stream
                 * @param marker_read
                 * @return a pointer to a chunk header.
                 */
                template<typename T>
                std::unique_ptr<chunk_header> make_chunk_header(const T &stream, bool marker_read) {
                    auto marker = rwio::read<char>(stream);
                    if (!marker_read) {
                        if ((marker) && (marker != iotdb::tsfile::file::CHUNK_HEADER)) {
                            throw std::runtime_error("Invalid header");
                        }
                    }
                    auto measurement_id = rwio::read<std::string>(stream);
                    auto data_size = rwio::read<int32_t>(stream);
                    auto data = rwio::read<int8_t>(stream);
                    auto num_pages = rwio::read<int32_t>(stream);
                    auto compression = rwio::read<int8_t>(stream);
                    auto encoding = rwio::read<int8_t>(stream);
                    if (measurement_id && data_size && num_pages && compression && encoding) {
                        // ok we can return the correct header
                        return std::make_unique<chunk_header>(measurement_id,
                                                              data_size,
                                                              static_cast<ts_datatype>(data),
                                                              static_cast<compression_type>(compression),
                                                              static_cast<ts_encoding>(encoding),
                                                              num_pages);

                    } else {
                        throw std::runtime_error("Invalid parsing header");
                    }
                }
            }
        }
}
#endif //IOTDB_NATIVE_CHUNK_HEADER_H
