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
#ifndef IOTDB_NATIVE_STATISTICS_H
#define IOTDB_NATIVE_STATISTICS_H
#include <tsfile/common/bytebuffer.h>
#include <tsfile/common/concepts.h>
#include <tsfile/model/datatypes.h>

#include <optional>

namespace tsfile {
template <typename T>
concept StatLike = requires(T a) {
    std::declval<T>().Count();
    std::declval<T>().StartTime();
    std::declval<T>().MinValue();
    std::declval<T>().MaxValue();
    std::declval<T>().FirstValue();
    std::declval<T>().LastValue();
    std::declval<T>().SumValue();
    std::declval<T>().Extreme();
};

template <typename T>
concept StatLikeHashable = StatLike<T> && Hashable<T>;

template <StatLike StatisticsImpl>
struct BaseStatistics : StatisticsImpl {};

///
/// @brief Generic class for statistics.
template <typename T>
class GenericStatistics {
    int64_t _count;
    int64_t _start_time;
    int64_t _end_time;
    std::optional<T> _min_value;
    std::optional<T> _max_value;
    std::optional<T> _first_value;
    std::optional<T> _last_value;
    std::optional<T> _sum_value;
    std::optional<T> _extreme;
    uint64_t _hashcode;

   public:
    auto Count() const { return _count; }
    auto StartTime() const { return _start_time; }
    auto EndTime() const { return _end_time; }
    auto MinValue() const { return _min_value; }
    auto MaxValue() const { return _max_value; }

    auto FirstValue() const { return _first_value; }
    auto LastValue() const { return _last_value; }
    auto SumValue() const { return _sum_value; }
    auto Extreme() const { return _extreme; }

    uint64_t HashCode() { return _hashcode; };
};

using generic_int = GenericStatistics<int>;
using IntStatistics = BaseStatistics<generic_int>;
using generic_float = GenericStatistics<float>;
using FloatStatistics = BaseStatistics<generic_float>;
using generic_double = GenericStatistics<double>;
using DoubleStatistics = BaseStatistics<generic_double>;
using generic_binary = GenericStatistics<ByteBuffer>;
using BinaryStatistics = BaseStatistics<generic_binary>;

///
/// @brief Statistics map that contains all kind of statistics.
///

class StatisticsMap {
    IntStatistics integer_stat_;
    FloatStatistics float_stat_;
    DoubleStatistics double_stat_;
    BinaryStatistics binary_stat_;

    TsDataType type_;

   public:
    ///
    /// @brief Constructor
    /// @param data data type to set. A TsDataType can be [ BOOLEAN, INT32, INT64, FLOAT, DOUBLE,
    /// TEXT, BINARY ]
    ///
    StatisticsMap(const TsDataType& data) : type_(data) {}
    ///
    /// @brief Constructor
    ///
    StatisticsMap(StatisticsMap&& m) {
        type_ = std::move(m.type_);
        integer_stat_ = std::move(m.integer_stat_);
        float_stat_ = std::move(m.float_stat_);
        double_stat_ = std::move(m.double_stat_);
        binary_stat_ = std::move(m.binary_stat_);
    }
    ///
    /// @brief Constructor
    ///
    StatisticsMap(const StatisticsMap& m) {
        type_ = m.type_;
        integer_stat_ = m.integer_stat_;
        float_stat_ = m.float_stat_;
        double_stat_ = m.double_stat_;
        binary_stat_ = m.binary_stat_;
    }
    ///
    /// @brief Constructor
    ///
    StatisticsMap& operator=(const StatisticsMap& m) {
        if (this != &m) {
            type_ = m.type_;
            integer_stat_ = m.integer_stat_;
            float_stat_ = m.float_stat_;
            double_stat_ = m.double_stat_;
            binary_stat_ = m.binary_stat_;
        }
        return *this;
    }
    ///
    /// Get the value
    ///

    template <StatLikeHashable T>
    T value() {
        switch (type_) {
            case TsDataType::INT32: {
                return integer_stat_;
            }
            case TsDataType::DOUBLE: {
                return double_stat_;
            }

            case TsDataType::BINARY: {
                return binary_stat_;
            }
            case TsDataType::FLOAT: {
                return float_stat_;
            }
            default:
                return float_stat_;
        }

        return integer_stat_;
    }
};

}  // namespace tsfile
#endif
