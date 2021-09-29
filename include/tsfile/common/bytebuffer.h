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
#ifndef IOTDB_COMMON_BYTEBUFFER
#define IOTDB_COMMON_BYTEBUFFER

#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include "common.h"

namespace iotdb::tsfile::common {

using std::istream;
using std::ostream;
///
///  @brief ByteBuffer/BasicByteBuffer work as Netty's ByteBuf
///  We've divided the buffer array in three segments:
///
///   +-------------------+------------------+------------------+
///   | discardable bytes |  readable bytes  |  writable bytes  |
///   |                   |     (CONTENT)    |                  |
///   +-------------------+------------------+------------------+
///   |                   |                  |                  |
///    0      <=      reader_index   <=   writer_index    <=    capacity
///
///  - redable bytes: This segment is where the actual data is stored. Any reading operation starts
///    the data at the current reader_index and increase it by the number of read bytes. If the argument of the 
///    read operation is also a bytebuffer and no destination index is specified, the specified buffer's writerIndex 
///    is increased together.
///  - discarable bytes: This segment contains the bytes which were read already by a read operation. 
///    Initially, the size of this segment is 0, but its size increases up to the writer_index as read operations are executed. 
///    The read bytes can be discarded by calling Discard() to reclaim unused area.
///  - writable bytes: This segment is a undefined space which needs to be filled. Any operation whose name starts with write will write the data at the current writerIndex and increase it by the number of written bytes. If the argument of the write operation is also a ByteBuf,
///    and no source index is specified, the specified buffer's readerIndex is increased together.
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
///  32, 50
///
/// BasicByteBuffer can be set to skip Index to get the normal buffer behaviour.
/// 
///   Example usage:
///   ByteBuffer buffer{10, 29, 31, 40, 6};
///   buffer.SkipIndexes();
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
/// The writable/redable mode is useful for concurrent in order to overlap writing and reading.
/// When we have consumed the writeable part. 

template <typename T>
class BasicByteBuffer {
   public:
    static constexpr unsigned int DEFAULT_SIZE = 1024;
    using internal_buffer = typename std::vector<T>;
    using value_type = T;
    using iterator = typename internal_buffer::iterator;
    using reverse_iterator = typename internal_buffer::reverse_iterator;
    using const_reverse_iterator = typename internal_buffer::const_reverse_iterator;
    using const_iterator = typename internal_buffer::const_iterator;

    ///
    /// @brief Default constructor
    ///
    BasicByteBuffer() { bytes_.reserve(DEFAULT_SIZE); }

    ///
    /// @brief Construct a byte array of predefined size
    /// @param n number of bytes that a bytearray should have
    ///
    explicit BasicByteBuffer(size_t n) : bytes_(n) {
        bytes_.reserve(n);
        reader_index_ = 0;
        writer_index_ = 0;
    }
    ///
    /// @brief Construct a byte array of predefined size using uniform init
    /// @param n number of bytes that a bytearray should have
    ///
    explicit BasicByteBuffer(const std::initializer_list<T>& bytes) {
        auto dim = bytes.size();
        reader_index_ = 0;
        bytes_.reserve(dim * 2);
        bytes_.insert(bytes_.end() + reader_index_, bytes.begin(), bytes.end());
    }
    ///
    /// @brief Copy Constructor
    /// @param buffer BasicByteBuffer to copy
    ///
    BasicByteBuffer(const BasicByteBuffer<T>& buffer) {}
    ///
    /// @brief Copy Assignment operator
    /// @param buffer BasicByteBuffer to copy
    //
    BasicByteBuffer& operator=(const BasicByteBuffer<T>& buffer) {}
    ///
    /// @brief Move Assignment operator
    /// @param buffer BasicByteBuffer to copy
    //
    BasicByteBuffer& operator=(BasicByteBuffer<T>&& buffer) {}
    /// 
    /// @brief Iterator in the buffer, in the reading zone.
    /// @return An iterator to the beginning of the given container c
    ///
    iterator Begin() noexcept { return (bytes_.begin()+reader_index_; }
    ///
    /// Iterator in the buffer
    /// @return an iterator to the end of the readable zone.
    ///
    iterator End() noexcept { return bytes_.end() - writer_index_; }
    ///
    /// iterator constant to the buffer
    /// @return a constant iterator to the beginning of readable zone
    ///
    const_iterator CBegin() const noexcept { return bytes_.cbegin() + reader_index_; }
    ///
    /// @brief iterator constant to the buffer
    /// @return a constant iterator to the end of the buffer
    ///
    const_iterator CEnd() const noexcept { return bytes_.cend() - writer_index_; }
    ///
    /// @brief reverse iterator to the begin of the buffer
    /// @return reverse iterator to the end of the buffer
    ///
    reverse_iterator RBegin() noexcept { return bytes_.rbegin() -writer_index_; }
    /**
     * reverse iterator to the end of the buffer
     * @return reverse iterator to the end of the buffer
     */
    reverse_iterator REnd() noexcept { return bytes_.rend() + reader_index_; }
    /**
     * constant reverse iterator to the begin of the buffer
     * @return constant reverse iterator to the end of the buffer
     */
    const_reverse_iterator CRBegin() const noexcept { return bytes_.crbegin(); }
    /**
     * constant reverse iterator to the begin of the buffer
     * @return constant reverse iterator to the end of the buffer
     */
    const_reverse_iterator CREnd() const noexcept { return bytes_.crend(); }

    ///
    /// @brief Discard byte operation. Please note that there is no guarantee about
    /// the content of writable bytes after calling Discard().
    /// The writable bytes will not be moved in most cases and could even be filled with completely
    /// different data depending on the underlying buffer implementation.
    /// Discard is for writing like std::move.

    void Discard() {
        auto scale = writer_index_ - reader_index_;
        reader_index_ = 0;
        writer_index_ = writer_index_ - scale;
    }
    /**
     * Double the reserved size for the byte buffer
     */
    void EnsureSpace() { bytes_.reserve(bytes_.capacity() * 2); }
    void Append(const BasicByteBuffer& data) {
        bytes_.emplace_back(data);
        // bytes_.emplace_back(data);
    }
    StatusRe Add(const T& data) {
        bytes_.emplace_back(data);
        // bytes_.emplace_back(data);
    }
    void Clear() { bytes_.clear(); }
    void Reserve(size_t size) { bytes_.reserve(size); }
    /**
     * Get the size of the byte buffer
     * @return size in byte of the buffer
     */
    size_t Size() const { return bytes_.size(); }
    /**
     * Get the real capacity of the buffer
     * @return
     */
    size_t Capacity() const { return bytes_.capacity(); }
    /**
     * Get the bytes converted in hexadecimal string
     * @return hexdecimal string of the bytebuffer
     */
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
    const BasicByteBuffer<T>& Set(size_t idx, const T& value) {
        bytes_.data()[idx] = value;
        return *this;
    }
    /**
     * Return the byte by random access
     * @param idx index of the byte
     * @return value of the byte
     */
    T& operator[](std::size_t idx) { return bytes_[idx]; }
    /**
     * Return the byte by random access
     * @param idx index of the byte
     * @return value of the byte
     */
    const T& operator[](std::size_t idx) const { return bytes_[idx]; }

    const T* Data() { return bytes_.data(); }

   private:
    std::vector<T> bytes_;
    uint64_t reader_index_{0};
    uint64_t writer_index_{0};
    template <typename V>
    friend bool operator==(const BasicByteBuffer<V>& lhs, const BasicByteBuffer<V>& rhs);
};

template <typename T>
bool operator==(const BasicByteBuffer<T>& lhs, const BasicByteBuffer<T>& rhs) {
    return lhs.hex().compare(rhs.hex()) == 0;
}
typedef BasicByteBuffer<byte> ByteBuffer;
}  // namespace iotdb::common

#endif  // IOTDB__UTIL__BYTEBUFFER
