//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <string>

#include "Yisp.h"
#include "Type.h"

namespace Yisp {
    class Printer {
    public:
        static std::string print(const Type::YispAST &ast);

        static std::string format_print(const std::string &ast);
    private:
        static std::string ast_to_string(const Type::YispAST &ast);
    };
}

#endif // PRINTER_H
