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
#ifndef IOTDB_NATIVE_DATAPOINT_H
#define IOTDB_NATIVE_DATAPOINT_H
#include <memory>
#include <optional>
#if 0
#include <tsfile/common/bytebuffer.h>
#include <tsfile/common/concepts.h>
#include <tsfile/model/datatypes.h>

namespace iotdb::tsfile {

template <typename T>
class GenericDataPoint {
    iotdb::tsfile::ts_datatype _type;
    std::string _measurement_id;
    std::optional<T> _value;

   public:
    GenericDataPoint(const ts_datatype& type, const std::string& measurement_id)
        : _type(type), _measurement_id(measurement_id) {}
    auto value() const { return _value; }
    auto measurement_id() const { return _measurement_id; }
    auto type() const { return _type; }
};
using IntegerDataPoint = GenericDataPoint<int>;
using LongDataPoint = GenericDataPoint<int64_t>;
using FloatDataPoint = GenericDataPoint<float>;
using DoubleDataPoint = GenericDataPoint<double>;
template <DataPoint DataPointImpl>
std::unique_ptr<DataPointImpl> MakeDataPoint(ts_datatype& type, std::string measurement_id) {
    switch (type) {
        case TsDataType::INT64: {
            return std::make_unique<LongDataPoint>(type, measurement_id);
        }
        case TsDataType::FLOAT: {
            return std::make_unique<FloatDataPoint>(type, measurement_id);
        }
        case TsDataType::DOUBLE: {
            return std::make_unique<DoubleDataPoint>(type, measurement_id);
        }
    }
    return std::make_unique<IntegerDataPoint>(type, measurement_id);
}

}  // namespace iotdb::tsfile
#endif
#endif
