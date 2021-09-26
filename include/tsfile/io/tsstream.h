
#ifndef IOTDB_NATIVE_TSSTREAM_H
#define IOTDB_NATIVE_TSSTREAM_H
#include <memory>
#include <string_view>

#include "macros.h"
#include "result.h"
#include <future>

namespace iotdb::tsfile::io {
using iotdb::tsfile::common;

class ts_istream {
   public:
    virtual int64_t count() const = 0;
    virtual result<io_status, std::shared_ptr<bytebuffer>> read(int64_t nbytes) = 0;
    //virtual std::future<result<file_status, std::shared_ptr<bytebuffer>>> read_async(
    //    int64_t nbytes) = 0;
    virtual result<io_status> read_next(const void** data, int64_t nbytes) = 0;
    virtual int skip(int count) = 0;
    virtual result<io_status> close() = 0;
    virtual ~ts_istream() = 0;

   private:
    IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(ts_istream)
};
class ts_ostream {
   public:
    virtual int64_t count() const = 0;
    virtual result<io_status> write(const bytebuffer& buffer) = 0;
    // virtual std::future<result<io_status>> write_async(const bytebuffer& buffer) = 0;
    virtual result<io_status> close() = 0;
    virtual ~ts_ostream() = 0;

   private:
    IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(ts_stream)
};
class ts_ifstream : public ts_istream {
   public:
    ts_ifstream(const std : string_view& filename) {}
    int64_t count() override const {};
    result<io_status, std::shared_ptr<bytebuffer>> read(int64_t nbytes) override {};
    //std::future<result<file_status, std::shared_ptr<bytebuffer>>> read_async(
    //    int64_t nbytes) override {}
    virtual result<io_status> read_next(const void** data, int64_t nbytes) override {}
    virtual int skip(int count) override {};
    virtual result<io_status> close() override {};
     ~ts_ifstream();
    IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(ts_ifstream)
};
class ts_ofstream : public ts_ostream {
   public:
    ts_ofstream(const std : string_view& filename) {}
    int64_t count() override {};
    result<io_status> write(const bytebuffer& buffer) override {};
    // std::future<result<io_status>> write_async(const bytebuffer& buffer) override {};
    result<io_status> close() override {};
    ~ts_ofstream() override{};
    IOTDB_NATIVE_DISALLOW_COPY_AND_ASSIGN(ts_ofstream)
};


}  // namespace iotdb::tsfile::io
#endif