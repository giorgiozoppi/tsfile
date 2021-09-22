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
#ifndef IOTDB_UTIL_BYTEBUFFER
#define IOTDB_UTIL_BYTEBUFFER

#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

namespace iotdb::util {

using std::istream;
using std::ostream;

template <typename T>
class basic_bytebuffer {
    std::vector<T> _bytes;

   public:
    static constexpr unsigned int DEFAULT_SIZE = 1024;
    using internal_buffer = typename std::vector<T>;
    using value_type = T;
    using iterator = typename internal_buffer::iterator;
    using reverse_iterator = typename internal_buffer::reverse_iterator;
    using const_reverse_iterator = typename internal_buffer::const_reverse_iterator;
    using const_iterator = typename internal_buffer::const_iterator;

    /**
     * default constructor
     */
    basic_bytebuffer() { _bytes.reserve(DEFAULT_SIZE); }
    /**
     * construct a byte array of predefined size
     * @param n number of bytes that a bytearray should have
     */
    explicit basic_bytebuffer(size_t n) : _bytes(n) { _bytes.reserve(n); }
    /**
     * construct a byte array of predefined size using uniform init
     * @param n number of bytes that a bytearray should have
     */
    basic_bytebuffer(const std::initializer_list<T>& bytes) {
        auto dim = bytes.size();
        _bytes.reserve(dim * 2);
        _bytes.insert(_bytes.end(), bytes.begin(), bytes.end());
    }
    /**
     * Move constructor
     * @param bytes
     */
    basic_bytebuffer(internal_buffer&& bytes) : _bytes(std::move(bytes)) {}
    /**
     * iterator in the buffer
     * @return an iterator to the beginning of the given container c
     */
    iterator begin() noexcept { return _bytes.begin(); }
    /**
     * iterator in the buffer
     * @return an iterator to the end of the given container c
     */
    iterator end() noexcept { return _bytes.end(); }
    /**
     * iterator constant to the buffer
     * @return a constant iterator to the beginning of the given container c
     */
    const_iterator cbegin() const noexcept { return _bytes.cbegin(); }
    /**
     * iterator constant to the buffer
     * @return a constant iterator to the end of the buffer
     */
    const_iterator cend() const noexcept { return _bytes.cend(); }
    /**
     * reverse iterator to the begin of the buffer
     * @return reverse iterator to the end of the buffer
     */
    reverse_iterator rbegin() noexcept { return _bytes.rbegin(); }
    /**
     * reverse iterator to the end of the buffer
     * @return reverse iterator to the end of the buffer
     */
    reverse_iterator rend() noexcept { return _bytes.rend(); }
    /**
     * constant reverse iterator to the begin of the buffer
     * @return constant reverse iterator to the end of the buffer
     */
    const_reverse_iterator crbegin() const noexcept { return _bytes.crbegin(); }
    /**
     * constant reverse iterator to the begin of the buffer
     * @return constant reverse iterator to the end of the buffer
     */
    const_reverse_iterator crend() const noexcept { return _bytes.crend(); }
    /**
     * Double the reserved size for the byte buffer
     */
    void ensure_space() { _bytes.reserve(_bytes.capacity() * 2); }
    /**
     * Get the size of the byte buffer
     * @return size in byte of the buffer
     */
    size_t size() const { return _bytes.size(); }
    /**
     * Get the real capacity of the buffer
     * @return
     */
    size_t capacity() const { return _bytes.capacity(); }
    /**
     * Get the bytes converted in hexadecimal string
     * @return hexdecimal string of the bytebuffer
     */
    const std::string hex() const {
        const char code[]{"0123456789ABCDEF"};
        std::ostringstream out;
        for (auto& b : _bytes) {
            auto num = b / 16;
            auto rest = b % 16;
            out << code[num];
            out << code[rest];
        }
        return out.str();
    }
    /**
     * Compare if two byte buffers are the same
     */
    bool operator==(const basic_bytebuffer<T>& bytebuffer) {
        return hex().compare(bytebuffer.hex()) == 0;
    }
    auto operator<=>(const basic_bytebuffer<T>& bytebuffer) { return hex() <=> bytebuffer.hex(); }
    //friend ostream& operator<<(ostream& os, const basic_bytebuffer<T>& bb);
    //istream& operator>>(istream& is, basic_bytebuffer<T>& dt);

    /**
     * Return the byte by random access
     * @param idx index of the byte
     * @return value of the byte
     */
    T& operator[](std::size_t idx) { return _bytes[idx]; }
    /**
     * Return the byte by random access
     * @param idx index of the byte
     * @return value of the byte
     */
    const T& operator[](std::size_t idx) const { return _bytes[idx]; }
};

typedef basic_bytebuffer<std::byte> bytebuffer;
template <typename T>
istream& operator>>(istream& is, basic_bytebuffer<T>& bb) {
    return is;
}
template <typename T>
ostream& operator<<(ostream& os, const basic_bytebuffer<T>& bb) {
    return os;
}

}  // namespace iotdb::util

#endif  // IOTDB__UTIL__BYTEBUFFER
