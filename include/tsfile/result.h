#ifndef IOTDB_NATIVE_RESULT_H
#define IOTDB_NATIVE_RESULT_H
#include <optional>
namespace iotdb::tsfile {
template <typename T, typename V> class result {
    std::optional<V> value() const {
        return _value;
    }
    private:
    V _value;
    T _error;

};

}
