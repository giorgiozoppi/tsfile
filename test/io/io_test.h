#include "tsstream.h"

namespace iotdb::tsfile::test {

class io_test  {
 public :
  // Test helpers.

  // Helper to write an array of data to an output stream.
  bool write_to_out(ts_ostream& output, const void* data, int size);

  // Helper to read a fixed-length array of data from an input stream.
  int ReadFromInput(ZeroCopyInputStream* input, void* data, int size);
  // Write a string to the output stream.
  void WriteString(ZeroCopyOutputStream* output, const std::string& str);
  // Read a number of bytes equal to the size of the given string and checks
  // that it matches the string.
  void ReadString(ZeroCopyInputStream* input, const std::string& str);
  // Writes some text to the output stream in a particular order.  Returns
  // the number of bytes written, in case the caller needs that to set up an
  // input stream.
  int WriteStuff(ZeroCopyOutputStream* output);
  // Reads text from an input stream and expects it to match what
  // WriteStuff() writes.
  void ReadStuff(ZeroCopyInputStream* input, bool read_eof = true);

  // Similar to WriteStuff, but performs more sophisticated testing.
  int WriteStuffLarge(ZeroCopyOutputStream* output);
  // Reads and tests a stream that should have been written to
  // via WriteStuffLarge().
  void ReadStuffLarge(ZeroCopyInputStream* input);

#if HAVE_ZLIB
  std::string Compress(const std::string& data,
                       const GzipOutputStream::Options& options);
  std::string Uncompress(const std::string& data);
#endif

  static const int kBlockSizes[];
  static const int kBlockSizeCount;
};
}

