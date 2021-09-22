#include "tsfile/model/chunk_group.h"

#include "tsfile/common/util.h"

namespace iotdb::tsfile {
std::byte chunk_group::delimiter() const { return _byte_delimiter; }
chunk_group_footer chunk_group::footer() const { return _footer; }
chunk_iterator chunk_group::begin() { return _chunks.begin(); }
chunk_iterator chunk_group::end() { return _chunks.end(); }
reverse_chunk_iterator chunk_group::rbegin() { return _chunks.rbegin(); }
reverse_chunk_iterator chunk_group::rend() { return _chunks.rend(); }
const_chunk_iterator chunk_group::cbegin() const { return _chunks.cbegin(); }
const_chunk_iterator chunk_group::cend() const { return _chunks.cend(); }
void chunk_group::add_chunk(iotdb::tsfile::chunk&& chunk) { _chunks.push_back(std::move(chunk)); }
bool chunk_group::remove_chunk(const iotdb::tsfile::chunk& input) {
    return iotdb::util::hashed_remove(_chunks, input);
}

const_reverse_chunk_iterator chunk_group::crbegin() const { return _chunks.crbegin(); }
const_reverse_chunk_iterator chunk_group::crend() const { return _chunks.crend(); }
}  // namespace iotdb::tsfile