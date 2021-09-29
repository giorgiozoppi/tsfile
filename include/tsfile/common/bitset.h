
#include <bitset>
#include <memory>

#include <tsfile/common/common.h>

namespace iotdb::tsfile::common {
static constexpr uint32_t BITSET_SIZE = 128;
using basic_biset = std::bitset<BITSET_SIZE>;
// @brief BitSet is a variable length bitset with minimum size 128 bit
class BitSet {
   public:
    BitSet(size_t size);
    BitSet(const BitSet& set);

   private:
    std::unique_ptr<basic_biset> bitsetArray_;
};

}  // namespace iotdb::tsfile::common