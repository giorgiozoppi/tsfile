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
#ifndef IOTDB__RWIO__H
#define IOTDB__RWIO__H

#include <optional>
#include <string>

#include <tsfile/file/metadata/metadata.h>
#include <util/bconv.h>
#include <util/bytebuffer.h>
#include <util/buffer_window.h>

namespace iotdb { namespace util { namespace rwio {

template<class Stream, class Tp = bool>
struct impl {
    static std::optional<Tp> read(Stream& bstream) {
        const auto res = bstream.read_n(sizeof(Tp));
        if (!res) return {};

        return bconv::to<Tp>(res.value());
    }

    static size_t
    write(const Tp& /*data*/, Stream& /*stream*/) {
        return 0;
    }
};

template<class Stream>
struct impl<Stream, std::string> {
    static std::optional<std::string> read(Stream& bstream) {
        const auto len = impl<Stream, int32_t>::read(bstream);
        if (!len) return {};

        const auto res = bstream.read_n(len.value());
        if (!res) return {};

        return bconv::to<std::string>(res.value());
    }

    static size_t
    write(const std::string& /*data*/, Stream& /*stream*/) {
        return 0;
    }
};

template<class Stream>
struct impl<Stream, util::buffer_window> {
    static std::optional<util::buffer_window> read(Stream& bstream) {
        const auto len = impl<Stream, int32_t>::read(bstream);
        if (!len) return {};

        return bstream.read_n(len.value());
    }

    static size_t
    write(const std::string& /*data*/, Stream& /*stream*/) {
        return 0;
    }
};

/**( READ BASE TYPES )**/

template<typename Tp, typename InputStream>
std::optional<std::enable_if_t<!std::is_enum_v<Tp> && !std::is_array_v<Tp>, Tp>>
read(InputStream& stream) {
    return impl<InputStream, Tp>::read(stream);
}

/**( READ ENUMS )**/

template<typename Tp, typename InputStream>
std::optional<std::enable_if_t<std::is_enum_v<Tp>, Tp>>
read(InputStream& stream) {
    const auto res = read<int16_t>(stream);
    if (!res) return {};

    return static_cast<Tp>(res.value());
}

/**( READ ARRAYS )**/

template<typename Tp, typename InputStream, typename T = std::remove_extent_t<Tp>>
std::vector<std::enable_if_t<std::is_array_v<Tp>, T>>
read(InputStream &stream) {
    const auto len = read<int32_t>(stream);
    if (!len) return {};

    std::vector <T> res;
    res.reserve(len.value());
    for (int i = 0; i < len.value(); ++i) {
        res.push_back(read<T>(stream).value());
    }
    return res;
}

/**( WRITE )**/

template<typename Tp, typename OutputStream>
size_t
write(const Tp& data, OutputStream& stream) {
    return impl<OutputStream, Tp>::write(data, stream);
}

}}}

#endif // IOTDB__RWIO__H
