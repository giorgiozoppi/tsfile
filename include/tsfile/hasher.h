#ifndef IOTDB_NATIVE_CHUNK_HASHER_H
#define IOTDB_NATIVE_CHUNK_HASHER_H
#include <cstdint>
#include <tuple>
#include <vector>

namespace iotdb::tsfile {
class hasher {
   public:
    void add(double data);
    void add(long data);
    void add(int data);
    void add(unsigned int data);
    void add(float data);
    void add(unsigned long data);
    void add(std::byte data);
    uint64_t compute();

   private:
    void add_data(uint64_t data, std::vector<uint8_t>& value);
    uint64_t gen_key_part();
    std::vector<uint8_t> _data;
};
}  // namespace iotdb::tsfile
#endif
