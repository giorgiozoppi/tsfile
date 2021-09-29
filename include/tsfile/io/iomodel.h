#ifndef IOTDB_NATIVE_IO_MODEL_H
#define IOTDB_NATIVE_IO_MODEL_H
#if 0

#include <tsfile/common/bitmap.h>
#include <tsfile/common/tsconcepts.h>

#include <memory>
#include <string>
#include <vector>
namespace io::tsfile {

class Tablet {
   private:
    std::vector < std::unique_ptr<IMeasurementSchema> schemas;
    std::map<std::string, int32_t> measurement_index;
    std::vector<int64_t> timestamps;
    std::vector<io::tsfile::common::BitMap> _bitmaps;
    int32_t row_size;
    int32_t max_row_number;
    bool is_aligned;

   public:
    tablet(/* args */);
    ~tablet();
};
}  // namespace io::tsfile
#endif
#endif
