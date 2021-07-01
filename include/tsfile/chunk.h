//
// Created by jozoppi on 7/1/21.
//

#ifndef TSFILE_CHUNK_H
#define TSFILE_CHUNK_H
#include "chunk_header.h"
namespace iotdb::tsfile {
class chunk {
    chunk_header _header;
    std::byte _marker;

};
}


#endif //TSFILE_CHUNK_H
