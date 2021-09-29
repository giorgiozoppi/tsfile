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

#ifndef IOTDB_NATIVE_SCHEMA_H
#define IOTDB_NATIVE_SCHEMA_H
#include <filesystem>
#include <map>
#include <utility>

#include "schema.h"

namespace iotdb::tsfile {
class IMeasurementSchema {
   public:
    virtual std::string GetMeasurementId() = 0;

  CompressionType getCompressor();

  TSEncoding getEncodingType();

  TSDataType getType();

  void setType(TSDataType dataType);

  TSEncoding getTimeTSEncoding();

  Encoder getTimeEncoder();

  Encoder getValueEncoder();

  Map<String, String> getProps();

  List<String> getSubMeasurementsList();

  List<TSDataType> getSubMeasurementsTSDataTypeList();

  List<TSEncoding> getSubMeasurementsTSEncodingList();

  List<Encoder> getSubMeasurementsEncoderList();

  int getSubMeasurementIndex(String measurementId);

  int getSubMeasurementsCount();

  /* test whether the schema contains Measurement with given measurementId */
  boolean containsSubMeasurement(String measurementId);

  int serializeTo(ByteBuffer buffer);

  int serializeTo(OutputStream outputStream) throws IOException;


    uint64_t hashcode() { return _hashcode; }
};
class schema {
   public:
    schema() {}
    schema(std::map<std::filesystem::path, std::unique_ptr<measurement_schema>>&& measurement) {
        _registered_timeseries = std::move(measurement);
    }
    void register_time_series(const std::filesystem::path& path,
                              std::unique_ptr<measurement_schema>&& descriptor) {
        _registered_timeseries.insert({path, std::move(descriptor)});
    }

   private:
    std::map<std::filesystem::path, std::unique_ptr<measurement_schema>> _registered_timeseries;
};
}  // namespace iotdb::tsfile
#endif
