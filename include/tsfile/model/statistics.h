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
#include <optional>

#include "tsfile/common/bytebuffer.h"
#include "tsfile/common/tsconcepts.h"
#include "tsfile/model/datatypes.h"

namespace iotdb::tsfile {

template <StatLikeHashable StatisticsImpl>
struct BaseStatistics : StatisticsImpl {};

template <typename T>
class GenericStatistics {
    long _count;
    long _start_time;
    long _end_time;
    std::optional<T> _min_value;
    std::optional<T> _max_value;
    std::optional<T> _first_value;
    std::optional<T> _last_value;
    std::optional<T> _sum_value;
    std::optional<T> _extreme;
    uint64_t _hashcode;

   public:
    long count() const { return _count; }
    long start_time() const { return _start_time; }
    long end_time() const { return _end_time; }
    auto min_value() const { return _min_value; }
    auto max_value() const { return _max_value; }

    auto first_value() const { return _first_value; }
    auto last_value() const { return _last_value; }
    auto sum_value() const { return _sum_value; }
    auto extreme() const { return _extreme; }

    uint64_t hash_code() { return _hashcode; };
};
using generic_int = GenericStatistics<int>;
using statistics_int = BaseStatistics<generic_int>;
using generic_float = GenericStatistics<float>;
using statistics_float = BaseStatistics<generic_float>;
using generic_double = GenericStatistics<double>;
using statistics_double = BaseStatistics<generic_double>;
using generic_binary = GenericStatistics<iotdb::common::bytebuffer>;
using statistics_binary = BaseStatistics<generic_binary>;

// using stat_ptr = template <typename T> std::unique_ptr<BaseStatistics<GenericStatistics<T>>;
class stat_container {
    statistics_int _integer_stat;
    statistics_float _float_stat;
    statistics_double _double_stat;
    statistics_binary _binary_stat;

    ts_datatype _type;

   public:
    stat_container(const ts_datatype& data) : _type(data) {}
    stat_container(stat_container&& m) {
        _type = std::move(m._type);
        _integer_stat = std::move(m._integer_stat);
        _float_stat = std::move(m._float_stat);
    }
    stat_container(const stat_container& m) {
        _type = m._type;
        _integer_stat = m._integer_stat;
        _float_stat = m._float_stat;
    }
    stat_container& operator=(const stat_container& m) {
        if (this != &m) {
            _type = m._type;
            _integer_stat = m._integer_stat;
            _float_stat = m._float_stat;
        }
        return *this;
    }

    ~stat_container() = default;
    template <StatLikeHashable StatisticsImpl>
    StatisticsImpl value() {
        switch (_type) {
            case ts_datatype::INT32: {
                return _integer_stat;
            }
            case ts_datatype::DOUBLE: {
                return _double_stat;
            }

            case ts_datatype::BINARY: {
                return _binary_stat;
            }
            case ts_datatype::FLOAT: {
                return _float_stat;
            }
            default:
                return _float_stat;
        }

        return _integer_stat;
    }
};

}  // namespace iotdb::tsfile
#endif
