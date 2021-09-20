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
    uint64_t compute() const;

   private:
    void add_data(uint64_t data);
    std::vector<std::byte> _data;
};
}  // namespace iotdb::tsfile
#endif
