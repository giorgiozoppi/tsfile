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
#ifndef IOTDB__TSFILE__READ__TSFILE__H
#define IOTDB__TSFILE__READ__TSFILE__H

#include <fstream>
#include <filesystem>

#include <util/bytebuffer.h>

namespace iotdb { namespace tsfile { namespace read {

class tsfile {
public:
    using fstream = std::basic_ifstream<util::bytebuffer::value_type>;
    using pos_type = fstream::pos_type;

private:
    std::filesystem::path _path;
    fstream _file_input;
    pos_type _beg;
    pos_type _end;
    pos_type _cur;

public:
    explicit tsfile(const std::filesystem::path path) {
        _path = path;
        _file_input.open(_path.c_str());
        _beg = _file_input.tellg();
        _file_input.seekg(0, _file_input.end);
        _end = _file_input.tellg();
        _file_input.seekg(0, _file_input.beg);
    }

    pos_type beg() const {
        return _beg;
    }

    pos_type end() const {
        return _end;
    }

    pos_type cur() const {
        return _cur;
    }

    size_t size() const {
        return _end - _beg;
    }

    void pos(const pos_type pos) {
        _file_input.seekg(pos);
    }

    void read(util::bytebuffer& buf) {
        _file_input.read(&buf[0], buf.size());
    }

    void read(util::bytebuffer& buf, const pos_type position) {
        pos_type cur = _file_input.tellg();
        _file_input.seekg(position);
        read(buf);
        _file_input.seekg(cur);
    }
};

}}}

#endif // IOTDB__TSFILE__READ__TSFILE__H
