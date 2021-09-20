
#include "tsfile/hasher.h"

#include <cstring>
#include <cstdint>
#include "tsfile/siphash.h"

namespace iotdb::tsfile {

typedef union {
    std::byte array[8];
    uint64_t data;
} bitarray_t;

void hasher::add_data(uint64_t data) {
    bitarray_t ba;
    ba.data = data;
    for (auto b : ba.array) {
        _data.emplace_back(b);
    }
}

void hasher::add(double data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(current));
    add_data(current);
}
void hasher::add(float data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current);
}
void hasher::add(long data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current);
}
void hasher::add(int data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current);
}
void hasher::add(unsigned int data) {
    uint64_t current;
    memcpy(&current, &data, sizeof(data));
    add_data(current);
}
uint64_t hasher::compute() const { 
    //1 include random key, get 16 bytes
    // get the input.
    // get 16 bytes outpuy
    // sum them
    return 9; }
}  // namespace iotdb::tsfile
