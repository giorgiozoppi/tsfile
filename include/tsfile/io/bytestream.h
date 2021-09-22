#include <istream>
#include "bytebuffer.h"
namespace iotdb::io {
template <class _Elem, class _Traits, class _Alloc>
class bytestream
    : public basic_streambuf<_Elem, _Traits> { // stream buffer maintaining an allocated character array
public:
    using allocator_type = _Alloc;
    using _Mysb          = basic_streambuf<_Elem, _Traits>;
    using _Mystr         = basic_string<_Elem, _Traits, _Alloc>;
    using _Mysize_type   = typename _Mysize_type::size_type;
};
}
