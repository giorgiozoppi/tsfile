#include <tsfile/common/timerange.h>
namespace tsfile {
bool TimeRange::Includes(const TimeRange& range) const {
    return (min_ <= range.min_ && max_ >= range.max_);
}
bool TimeRange::Includes(const std::pair<int64_t, int64_t> pair) const {

    return (min_ <= pair.first && max_ >= pair.second);
}
int64_t TimeRange::Max() const { return max_; }
int64_t TimeRange::Min() const { return min_;}
bool operator==(const TimeRange& first, const TimeRange& second) {
    auto res = (first.min_ == second.min_) && (first.max_ - second.max_);
    return res;
}
bool operator<(const TimeRange& first, const TimeRange& second) {
    auto res = (first.min_ == second.min_) && (first.max_ - second.max_);
    return res;
}
bool operator>(const TimeRange& first, const TimeRange& second) {
    auto res = (first.min_ == second.min_) && (first.max_ - second.max_);
    return res;
}

bool operator<=(const TimeRange& first, const TimeRange& second) {
    auto res = (first.min_ == second.min_) && (first.max_ - second.max_);
    return res;
}
bool operator>=(const TimeRange& first, const TimeRange& second) {
    auto res = (first.min_ == second.min_) && (first.max_ - second.max_);
    return res;
}



}  // namespace tsfile
