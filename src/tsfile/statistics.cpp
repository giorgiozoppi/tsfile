#include "tsfile/statistics.h"

namespace iotdb::tsfile {
long statistics::count() const { return _count; }
long statistics::start_time() const { return _start_time; }
long statistics::end_time() const { return _end_time; }
double statistics::min_value() const { return _min_value; }
double statistics::max_value() const { return _max_value; }
double statistics::first_value() const { return _first_value; }
double statistics::last_value() const { return _last_value; }
double statistics::sum_value() const { return _sum_value; }
double statistics::extreme() const { return _extreme; }
long statistics::hash_code() const { return _hashcode; }
}  // namespace iotdb::tsfile