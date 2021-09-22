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
#ifndef IOTDB__TSFILE__READ__SEQUENCE_READER__H
#define IOTDB__TSFILE__READ__SEQUENCE_READER__H

#include <filesystem>
#include <optional>

#include "tsfile/common/bytebuffer.h"

namespace iotdb::tsfile {

class sequence_reader {
    const std::string MAGIC_STRING = "TsFile";
    const std::string VERSION_NUMBER = "000001";

    //    tsfile _tsfile_input;
    int32_t _metadata_size;
    std::size_t _metadata_pos;
    std::filesystem::path _path;
    //    std::optional<iotdb::tsfile::file::metadata::file_metadata> _file_metadata;

   public:
    explicit sequence_reader(const std::filesystem::path& path) : _path(path) {}
    /*
        explicit sequence_reader(const std::filesystem::path& path, const bool load_metadata_size_):
       _tsfile_input{path} { _metadata_size = -1; _metadata_pos = -1; if (load_metadata_size_) {
                load_metadata_size();
            }
        }

        void load_metadata_size() {
            if (MAGIC_STRING == read_tail_magic()) {
                int read_size = MAGIC_STRING.size() + sizeof(int32_t);
                util::bytebuffer metadata_size(read_size);
                tsfile::pos_type offset = _tsfile_input.end() - std::streamoff(read_size);
                _tsfile_input.read(metadata_size, offset);
                util::buffer_window metadata_size_win{metadata_size};
                //metadataSize.flip();
                _metadata_size = rwio::read<int32_t>(metadata_size_win).value();
                _metadata_pos = offset - std::streamoff(_metadata_size) - _tsfile_input.beg();
            }
        }

        std::string read_version_number() {
            std::size_t version_number_size = VERSION_NUMBER.size();
            util::bytebuffer version_number(version_number_size);
            _tsfile_input.read(version_number, _tsfile_input.beg() +
       std::streamoff(MAGIC_STRING.size()));
            //versionNumberBytes.flip();
            return std::string(version_number.begin(), version_number.end());
        }

        std::string read_tail_magic() {
            std::size_t magic_string_size = MAGIC_STRING.size();
            util::bytebuffer tail_magic(magic_string_size);
            _tsfile_input.read(tail_magic, _tsfile_input.end() - std::streamoff(magic_string_size));
            //magicStringBytes.flip();
            return std::string(tail_magic.begin(), tail_magic.end());
        }

        std::string read_head_magic(bool move_position = false) {
            std::size_t magic_string_size = MAGIC_STRING.size();
            util::bytebuffer head_magic(magic_string_size);
            if (move_position) {
                _tsfile_input.pos(0);
                _tsfile_input.read(head_magic);
            } else {
                _tsfile_input.read(head_magic, 0);
            }
            //magicStringBytes.flip();
            return std::string(head_magic.begin(), head_magic.end());
        }

        int32_t metadata_size() const {
            return _metadata_size;
        }

        std::size_t metadata_pos() const {
            return _metadata_pos;
        }

        bool is_complete() {
            return
                _tsfile_input.size() >= MAGIC_STRING.size()*2 + VERSION_NUMBER.size() &&
                read_tail_magic() == read_head_magic();
        }

        encoding::endian_type endian_type() const {
            return _endian_type;
        }

        iotdb::tsfile::file::metadata::file_metadata read_file_metadata() {
            if (!_file_metadata) {
                util::bytebuffer buf(_metadata_size);
                _tsfile_input.read(buf, _metadata_pos);
                util::buffer_window bwin{buf};
                _file_metadata = iotdb::tsfile::file::metadata::make_file_metadata(bwin);
            }
            return _file_metadata.value();
        }
        */
};
}  // namespace iotdb::tsfile

#endif  // IOTDB__TSFILE__READ__SEQUENCE_READER__H
