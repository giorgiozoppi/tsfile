#ifndef IOTDB_NATIVE_TIME_RANGE_H
#define IOTDB_NATIVE_TIME_RANGE_H
#include <algorithm>
#include <chrono>
namespace tsfile {
struct TimeRange final {
    TimeRange(int64_t min, int64_t max) : min_(min), max_(max) {}
    bool Includes(const TimeRange& range) const;
    bool Includes(const std::pair<int64_t, int64_t> pair) const;
    int64_t Max() const;
    int64_t Min() const;
    friend bool operator==(const TimeRange& first, const TimeRange& second);
    friend bool operator<=(const TimeRange& first, const TimeRange& second);
    friend bool operator>=(const TimeRange& first, const TimeRange& second);
    friend bool operator<(const TimeRange& first, const TimeRange& second);
    friend bool operator>(const TimeRange& first, const TimeRange& second);

   private:
    int64_t min_{0};
    int64_t max_{0};
};

}  // namespace tsfile
#endif