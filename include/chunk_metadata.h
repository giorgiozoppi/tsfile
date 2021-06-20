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
#ifndef IOTDB_NATIVE_CHUNK_METADATA_H
#define IOTDB_NATIVE_CHUNK_METADATA_H

#include <util/bytebuffer.h>
#include <cstdint>
#include <system_error>
#include <iostream>
#include <tsfile/file/metadata/metadata.h>
#include <tsfile/file/metadata/statistics.h>


namespace iotdb {
    namespace tsfile {
        namespace file {
            namespace metadata {
                class chunk_metadata {
                public:
                    /**
                     *
                     * @param measurementUid
                     * @param datatype
                     * @param fileOffset
                     * @param statistics
                     */
                    explicit chunk_metadata(const std::string &measurementUid,
                                   const ts_datatype &datatype,
                                   int64_t fileOffset,
                                   const statistics& stat);
                    /**
                     *
                     * @param buffer
                     * @return
                     */
                    std::error_code read_from(const iotdb::util::bytebuffer &buffer);

                    /**
                     *
                     * @param stream
                     * @return
                     */
                    std::error_code write_to(std::ostream &stream);

                    /**
                     *
                     */
                    friend std::ostream &operator<<(std::ostream &os, const chunk_metadata &p);

                private:
                    std::string _measurementUid;
                    /**
                     * Byte offset of the corresponding data in the file Notice: include the chunk header and marker.
                     */
                    int64_t _offsetOfChunkHeader;

                    ts_datatype _tsDataType;

                    /**
                     * version is used to define the order of operations(insertion, deletion, update). version is set
                     * according to its belonging ChunkGroup only when being queried, so it is not persisted.
                     */
                    int64_t _version;
                    /**
                     * All data with timestamp <= deletedAt are considered deleted.
                     */
                    int64_t _deletedAt;
                    bool _modified;
                };

                std::ostream &operator<<(std::ostream &os, const chunk_metadata &p);

            };
        }
    }
}
#endif //IOTDB_NATIVE_CHUNK_METADATA_H
