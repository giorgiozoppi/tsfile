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

#ifndef IOTDB_NATIVE_METADATA_H
#define IOTDB_NATIVE_METADATA_H
namespace tsfile {
enum class EndianType { IOTDB_NATIVE_BIG_ENDIAN, IOTDB_NATIVE_LITTLE_ENDIAN };

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
constexpr EndianType byte_order = EndianType::IOTDB_NATIVE_LITTLE_ENDIAN;
#else
constexpr EndianType byte_order = EndianType::IOTDB_NATIVE_BIG_ENDIAN;
#endif
///
/// @brief Supported compression types
///
enum class TsCompressionType { UNCOMPRESSED, SNAPPY, GZIP, LZO, SDT, PAA, PLA };
///
/// @brief Supported data type for the time series
///
enum class TsDataType { BOOLEAN, INT32, INT64, FLOAT, DOUBLE, TEXT, BINARY };
///
/// @brief Supported encoding type
///
enum class TsEncoding { PLAIN, PLAIN_DICTIONARY, RLE, DIFF, TS_2DIFF, BITMAP, GORILLA, REGULAR };

}  // namespace tsfile

#endif  // IOTDB_NATIVE_METADATA_H
