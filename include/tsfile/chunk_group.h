//
// Created by jozoppi on 7/1/21.
//

#ifndef TSFILE_CHUNK_GROUP_H
#define TSFILE_CHUNK_GROUP_H
#include <cstddef>
#include <vector>
#include "chunk.h"
#include "chunk_group_footer.h"
namespace iotdb::tsfile {
    class chunk_group {
        std::vector<chunk> _chunks;
        std::byte _byte_delimiter;
        chunk_group_footer _footer;
    };
}


#endif //TSFILE_CHUNK_GROUP_H
