#include "tsfile/model/page_header.h"

namespace iotdb::tsfile {
page_header::page_header(int uncompressed_size, int compressed_size)
    : uncompressed_size(uncompressed_size), compressed_size(compressed_size) {}
int page_header::uc_size() const { return uncompressed_size; }
int page_header::c_size() const { return compressed_size; }
void page_header::add_statistic(const iotdb::tsfile::statistics& statistics) {
    _statistics.emplace_back(statistics);
}
bool page_header::remove_statistic(const iotdb::tsfile::statistics& stat) {
    auto pos = std::remove_if(std::begin(_statistics), std::end(_statistics),
                              [=](auto value) { return value.hash_code() == stat.hash_code(); });
    return (pos != _statistics.end());
}
stat_iterator page_header::begin() { return _statistics.begin(); }
stat_iterator page_header::end() { return _statistics.end(); }
reverse_stat_iterator page_header::rbegin() { return _statistics.rbegin(); }
reverse_stat_iterator page_header::rend() { return _statistics.rend(); }
const_stat_iterator page_header::cbegin() const { return _statistics.cbegin(); }
const_stat_iterator page_header::cend() const { return _statistics.cend(); }
const_reverse_stat_iterator page_header::crbegin() const { return _statistics.crbegin(); }
const_reverse_stat_iterator page_header::crend() const { return _statistics.crend(); }
}  // namespace iotdb::tsfile
