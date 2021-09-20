#ifndef IOTDB_NATIVE_STATISTICS_H
#define IOTDB_NATIVE_STATISTICS_H
namespace iotdb::tsfile {
class statistics {
    long _count;
    long _start_time;
    long _end_time;
    double _min_value;
    double _max_value;
    double _first_value;
    double _last_value;
    double _sum_value;
    double _extreme;
    long _hashcode;
   public:
    long count() const;
    long start_time() const;
    long end_time() const;
    double min_value() const;
    double max_value() const;
    double first_value() const;
    double last_value() const;
    double sum_value() const;
    double extreme() const;
    bool operator==(const statistics& value);
    bool operator<(const statistics& value);
    bool operator>(const statistics& value);
    bool operator>=(const statistics& value);
    bool operator<=(const statistics& value);
    long hash_code() const;
};
}  // namespace iotdb::tsfile
#endif
