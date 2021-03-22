//
// Created by YuzukiTsuru on 2021/3/21.
//

#ifndef YISP_FILEIO_H
#define YISP_FILEIO_H

#include <iostream>

namespace Yisp {
    class FileIO {
    public:
        static std::string read_from_file(const std::string& file_name);
    };
}


#endif //YISP_FILEIO_H
