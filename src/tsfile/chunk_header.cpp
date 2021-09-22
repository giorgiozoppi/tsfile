#include "model/chunk_header.h"

namespace iotdb::tsfile {
/**
 * Class that holds the responsibility to model a chunk header
 */

chunk_header::chunk_header(const std::string& measurementID, int dataSize, ts_datatype dataType,
                           compression_type compressionType, ts_encoding encoding, int numOfPages)
    : _measurement_id(measurementID),
      _data_size(dataSize),
      _datatype(dataType),
      _compression_type(compressionType),
      _encoding_type(encoding),
      _num_of_pages(numOfPages) {}
/**
 * Get measurement identifier
 * @return the measurement id
 */
std::string chunk_header::get_measurement_id() const { return _measurement_id; }

/**
 * Get the data size.
 */
size_t chunk_header::get_data_size() const { return _data_size; }

/**
 * Set measurement identifier
 * @param id
 */
void chunk_header::set_measurement_id(const std::string& id) { _measurement_id = id; }

/**
 * Get the compression type.
 * @return compression type
 */
compression_type chunk_header::get_compression_type() const { return _compression_type; }

/**
 * Set the compression type
 * @param type of the compression.
 */

void chunk_header::set_compression_type([[maybe_unused]] const compression_type& type) {
    this->_compression_type = type;
}

/**
 * Get the time series data type
 * @return time series data type
 */
ts_datatype chunk_header::get_ts_datatype() const { return _datatype; }

/**
 * Set the time series data type
 */
void chunk_header::set_ts_datatype(const ts_datatype& type) { _datatype = type; }

/**
 * Get the time series data type
 * @return time series encoding.
 */
ts_encoding chunk_header::get_ts_encoding() const { return _encoding_type; }

/**
 * Set the time series encoding
 * @param type series encoding
 */
void chunk_header::set_ts_encoding(const ts_encoding& type) { _encoding_type = type; }

/**
 * Get number of pages
 * @return current number of pages.
 */

int chunk_header::get_num_of_pages() const { return _num_of_pages; }

/**
 * Set the number of paging
 * @param num_of_pages
 */
void chunk_header::set_num_of_pages(const int& num_of_pages) { _num_of_pages = num_of_pages; }

uint64_t chunk_header::hash_code() const { return _hashcode; }
uint64_t chunk_header::compute_hash() { return 0; }

}  // namespace iotdb::tsfile
