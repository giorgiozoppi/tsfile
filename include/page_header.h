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

#include <tsfile/file/metadata/statistics.h>
#include <tsfile/file/header/chunk_header.h>
#include <tsfile/file/markers.h>


#include <util/rwio.h>

namespace iotdb::tsfile::file {
            class page_header {
            public:
                /**
                 *
                 * @param uncompressed_size
                 * @param compressed_size
                 * @param stat
                 * @param modified
                 */
                explicit page_header(int uncompressed_size,
                                     int compressed_size,
                                     const iotdb::tsfile::file::statistics &stat,
                                     bool modified);

                void set_uncompressed_size(int uncompressed) noexcept;

                int get_uncompressed_size() const noexcept;

                
                void set_compressed_size(int uncompressed) noexcept;

                int get_compressed_size() const noexcept;

                iotdb::tsfile::file::statistics get_statistics() const noexcept;

                void set_statistics(const iotdb::tsfile::file::statistics &statistics);


                bool is_modified() const noexcept;

                void set_modified(bool modified) noexcept;
                std::string str() const;


            private:
                int _uncompressed_size;
                int _compressed_size;
                iotdb::tsfile::file::statistics _statistics;
                bool _modified;
            };
            /**
             * Create a header from a stream or a buffer.
             * @tparam T  stream or buffer to be used.
             * @param stream
             * @param marker_read
             * @return a pointer to a chunk header.
             */
            template<typename T>
            std::unique_ptr<iotdb::tsfile::file::page_header> make_page_header(const T &stream) {
                auto uncompressed_siz = util::rwio::read<std::int32_t>(stream);
                auto compressed_siz = util::rwio::read<std::int32_t>(stream);
                auto stats = util::rwio::read<iotdb::tsfile::file::statistics>(stream);
                if (uncompressed_siz && compressed_siz && stats) {
                    // ok we can return the correct header
                    return std::make_unique<tsfile::file::page_header>(uncompressed_siz, compressed_siz, stats);
                } else {
                    throw std::runtime_error("Invalid parsing header");
                }
            }
        }
    }
}
#endif //IOTDB_NATIVE_PAGE_HEADER_H
