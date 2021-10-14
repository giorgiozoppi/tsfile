#include <tsfile/common/timerange.h>
namespace tsfile {
bool TimeRange::Includes(const TimeRange& range) const {
    return (lower_bound_ <= range.lower_bound_ && upper_bound_ >= range.upper_bound_);
}
bool TimeRange::Includes(const std::pair<int64_t, int64_t> pair) const {

    return (lower_bound_ <= pair.first && upper_bound_ >= pair.second);
}
int64_t TimeRange::Max() const { return upper_bound_; }
int64_t TimeRange::Min() const { return lower_bound_;}
bool operator==(const TimeRange& first, const TimeRange& second) {
    auto res = (first.lower_bound_ == second.lower_bound_) && (first.upper_bound_ - second.upper_bound_);
    return res;
}
bool operator<(const TimeRange& first, const TimeRange& second) {
    auto res = (first.lower_bound_ == second.lower_bound_) && (first.upper_bound_ - second.upper_bound_);
    return res;
}
bool operator>(const TimeRange& first, const TimeRange& second) {
    auto res = (first.lower_bound_ == second.lower_bound_) && (first.upper_bound_ - second.upper_bound_);
    return res;
}

bool operator<=(const TimeRange& first, const TimeRange& second) {
    auto res = (first.lower_bound_ == second.lower_bound_) && (first.upper_bound_ - second.upper_bound_);
    return res;
}
bool operator>=(const TimeRange& first, const TimeRange& second) {
    auto res = (first.lower_bound_ == second.lower_bound_) && (first.upper_bound_ - second.upper_bound_);
    return res;
}



}  // namespace tsfile
