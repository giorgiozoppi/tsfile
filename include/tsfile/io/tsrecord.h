#ifndef IOTDB_NATIVE_RECORD_H
#define IOTDB_NATIVE_RECORD_H
#include <memory>
#include <string>
#include <vector>
#if 0
#include "tsconcepts.h"

namespace iotdb::tsfile::io {
/* @brief TsRecord
 *
 */
class TsRecord {
    using DataPointPtr = std::unique_ptr<DataPoint>;
    /** timestamp of this TSRecord. */
    int64_t timestamp_;
    /** deviceId of this TSRecord. */
    std::string device_id_;
    /** all value of this TSRecord. */
    std::vector<DataPointPtr> data_point_list_;

   public:
    /// @brief TsRecord Constructor
    /// @param timestamp  Creation Timestamp
    /// @param device_id  Device Identifier
    TsRecord(int64_t timestamp, const std::string& device_id)
        : timestamp_(timestamp), device_id_(device_id) {}

    // @brief Set the currentTime stamp
    //
    void SetTimestamp(long timestamp) { timestamp_ = timestamp; }
    int64_t Time() const { return timestamp_; }
    TsRecord AddTuple(DataPointPtr&& ptr) { data_point_list_.push_back(std::move(ptr)); }
};
}  // namespace iotdb::tsfile::io
#endif
#endif
