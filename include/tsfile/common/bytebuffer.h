/**
 * Copyright (c) 2021 Giorgio Zoppi <giorgio.zoppi@iotdbe.com>
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IOTDB_COMMON_BYTEBUFFER
#define IOTDB_COMMON_BYTEBUFFER

#include <tsfile/common/common.h>
#include <tsfile/common/murmurhash3.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <vector>

namespace tsfile {

///
///  @brief ByteBuffer/BasicByteBuffer are an abstraction for an array of bytes.
///         the data are backed now within a STL vector but it might change in the future,
///         the interface will remain the same.
///         We store always the arithmetic_types: float, double, int, long, unsigned long in big
///         endian.
///   Example usage:
///   ByteBuffer buffer{10, 29, 31, 40, 6};
///   for(auto& i: buffer) {
///     std::cout << i << ", "
///   }
///   std::cout << std::endl;
///   buffer.Add(32);
///   buffer.Add(50);
///   for(auto& i: buffer) {
///     std::cout << i << ", "
///   }
///  We will see:
///  10, 29, 31, 40, 6,
///  10, 29, 31, 40, 6, 32, 50

template <typename T>
class BasicByteBuffer {
   public:
    static constexpr unsigned int kBufferDefaultSize = 1024;
    using internal_buffer = typename std::vector<T>;
    using value_type = T;
    using iterator = typename internal_buffer::iterator;
    using reverse_iterator = typename internal_buffer::reverse_iterator;
    using const_reverse_iterator = typename internal_buffer::const_reverse_iterator;
    using const_iterator = typename internal_buffer::const_iterator;

    ///
    /// @brief Default constructor
    ///
    BasicByteBuffer() { bytes_.reserve(kBufferDefaultSize); }

    ///
    /// @brief Construct a byte array of predefined size
    /// @param n number of bytes that a bytearray should have
    ///
    explicit BasicByteBuffer(size_t n) : bytes_(n) { bytes_.reserve(n); }
    ///
    /// @brief Construct a byte array of predefined size using uniform init
    /// @param n number of bytes that a bytearray should have
    ///
    explicit BasicByteBuffer(const std::initializer_list<T>& bytes) {
        auto dim = bytes.size();
        bytes_.reserve(dim * 2);
        bytes_.insert(bytes_.end(), bytes.begin(), bytes.end());
    }
    ///
    /// @brief Copy Constructor
    /// @param buffer BasicByteBuffer to copy
    ///
    BasicByteBuffer(const BasicByteBuffer<T>& buffer) : bytes_(buffer.bytes_) {}
    ///
    /// @brief Copy Assignment operator
    /// @param buffer BasicByteBuffer to copy
    //
    BasicByteBuffer& operator=(const BasicByteBuffer<T>& buffer) {
        if (this != &buffer) {
            bytes_ = buffer.bytes_;
        }
        return *this;
    }
    ///
    /// @brief Move Assignment operator
    /// @param buffer BasicByteBuffer to copy
    //
    BasicByteBuffer& operator=(BasicByteBuffer<T>&& buffer) {
        if (this != &buffer) {
            bytes_ = std::move(buffer.bytes_);
        }
        return *this;
    }
    ///
    /// @brief Iterator in the buffer, in the reading zone.
    /// @return An iterator to the beginning of the given container c
    ///
    iterator begin() noexcept { return bytes_.begin(); }
    ///
    /// Iterator in the buffer
    /// @return an iterator to the end of the readable zone.
    ///
    iterator end() noexcept { return bytes_.end(); }
    ///
    /// iterator constant to the buffer
    /// @return a constant iterator to the beginning of readable zone
    ///
    const_iterator cbegin() const noexcept { return bytes_.cbegin(); }
    ///
    /// @brief iterator constant to the buffer
    /// @return a constant iterator to the end of the buffer
    ///
    const_iterator cend() const noexcept { return bytes_.cend(); }
    ///
    /// @brief reverse iterator to the begin of the buffer
    /// @return reverse iterator to the end of the buffer
    ///
    reverse_iterator rbegin() noexcept { return bytes_.rbegin(); }
    ///
    /// @brief reverse iterator to the end of the buffer
    /// @return reverse iterator to the end of the buffer
    ///
    reverse_iterator rend() noexcept { return bytes_.rend(); }
    ///
    /// @brief  constant reverse iterator to the begin of the buffer
    /// @return constant reverse iterator to the end of the buffer
    ///
    const_reverse_iterator crbegin() const noexcept { return bytes_.crbegin(); }
    ///
    /// @brief constant reverse iterator to the begin of the buffer
    /// @return constant reverse iterator to the end of the buffer
    ///
    const_reverse_iterator crend() const noexcept { return bytes_.crend(); }
    ///
    /// @brief Append a buffer inside the byte buffer
    /// @param  data  buffer to append
    ///
    void Append(const BasicByteBuffer& data) {
        std::copy(std::begin(data), std::end(data), std::back_inserter(bytes_));
    }
    ///
    /// @brief Append a buffer inside the byte buffer
    /// @param  data  buffer to append
    ///

    void Append(const std::vector<unsigned char>& data) {
        if (std::is_same_v<T, unsigned char>) {
            std::copy(std::begin(data), std::end(data), std::back_inserter(bytes_));
        } else {
            throw std::invalid_argument("cannot push incompatible data");
        }
    }
    ///
    /// @brief Append a buffer inside the byte buffer avoiding temporary
    /// @param  data  buffer to append
    ///

    void Append(std::vector<Byte>&& data) {
        if (std::is_same_v<T, Byte>) {
            std::copy(std::begin(data), std::end(data), std::back_inserter(bytes_));
        } else {
            throw std::invalid_argument("cannot push incompatible data");
        }
    }

    ///
    /// @brief Add an item to the buffer
    /// @param data item to add.
    ///
    void Add(const T& data) { bytes_.emplace_back(data); }
    ///
    /// @brief Clear the buffer.
    ///
    void Clear() { bytes_.clear(); }
    ///
    /// @brief Reserve the buffer
    /// @param size size of the buffer.
    ///
    void Reserve(size_t size) { bytes_.reserve(size); }
    ///
    /// @brief Get the size of the byte buffer
    /// @return size in byte of the buffer
    ///
    size_t Size() const { return bytes_.size(); }
    ///
    /// Get the real capacity of the buffer
    /// @return
    ///
    size_t Capacity() const { return bytes_.capacity(); }
    ///
    /// Get the bytes converted in hexadecimal string
    /// @return hexdecimal string of the bytebuffer
    ///
    std::string Hex() const {
        const char code[]{"0123456789ABCDEF"};
        std::ostringstream out;
        for (auto& b : bytes_) {
            auto num = b / 16;
            auto rest = b % 16;
            out << code[num];
            out << code[rest];
        }
        return out.str();
    }
    ///
    /// @brief Supprot for the Hashable concept;
    /// @return hexdecimal string of the bytebuffer
    ///
    std::string GetHashCode() const noexcept { return Hex(); }
    ///
    /// @brief Support for the Hashable concept
    /// @return bytebuffer of the hash.
    /*
    ByteBuffer ByteHash() const noexcept {
        ByteBuffer out(16);
        std::random_device rd;
        std::mt19937 e{rd()};
        std::uniform_int_distribution<uint32_t> dist{0, std::numeric_limits<uint32_t>::max() - 1};
        auto seed = dist(e);
        MurmurHash3_x86_128(bytes_.size(), bytes_.size(), seed, out.Data());
        return out;
    }
    */
    ///
    /// @brief Return the byte by random access
    /// @param idx index of the byte
    /// @return value of the byte
    ///
    T& operator[](std::size_t idx) { return bytes_[idx]; }
    ///
    /// @brief Return the byte by random access
    /// @param idx index of the byte
    /// @return value of the byte
    ///
    const T& operator[](std::size_t idx) const { return bytes_[idx]; }
    ///
    /// @brief Return content hd the buffer
    /// @return value of the byte
    ///
    T* Data() { return bytes_.data(); }

   private:
    std::vector<T> bytes_;
    template <typename V>
    friend bool operator==(const BasicByteBuffer<V>& lhs, const BasicByteBuffer<V>& rhs);
};
template <typename T>
bool operator==(const BasicByteBuffer<T>& lhs, const BasicByteBuffer<T>& rhs) {
    return lhs.Hex().compare(rhs.Hex()) == 0;
}
typedef BasicByteBuffer<Byte> ByteBuffer;

}  // namespace tsfile

#endif  // IOTDB__UTIL__BYTEBUFFER
