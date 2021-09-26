#ifndef IOTDB_NATIVE_IOCONTEXT_H
#define IOTDB_NATIVE_IOCONTEXT_H

namespace iotdb::tsfile::io {
class io_context {
    std::future<>  post_write();
    std::future<>  post_read();

};
}
#endif
