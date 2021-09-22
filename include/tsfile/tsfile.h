/
// Created by jozoppi on 7/1/21.
//

#ifndef TSFILE_TSFILE_H
#define TSFILE_TSFILE_H
#include <array>
#include <cstddef>
#include <string>

    namespace iotdb::tsfile {
    class tsfile {
        std::string _magic_string;
        std::array<std::byte, 6> _version_number;

       public:
        const std::array<std::byte, 6> version() const { return _version_number; }
        const std::string magic_string() const { return _magic_string; }
    };
}

#endif  // TSFILE_TSFILE_H
