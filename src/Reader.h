//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef READER_H
#define READER_H

#include <iostream>
#include <regex>

#if MSVC
#include <optional>
#endif

#include "Yisp.h"
#include "Syntax.h"
#include "Type.h"

namespace Yisp {
    class Reader {
    public:
        explicit Reader(std::vector<std::string> tokens) : tokens{std::move(tokens)}, position{0} {}

        static Type::YispAST read(const std::string &program);

        static std::vector<std::string> tokenize(const std::string &text);

        Type::YispAST read_form();

        Type::YispAST read_list();

        Type::YispAST read_string();

        Type::YispAST read_atom();

    private:
        unsigned int position;

        std::vector<std::string> tokens;

        std::optional<std::string> next();

        std::optional<std::string> peek();

        bool out_of_bounds();

        static std::string clean(const std::string &text);

        static std::optional<double> token_to_number(const std::string &token);

        static std::vector<std::string> split(const std::string &text, const std::string &regex_str);
    };
}

#endif // READER_H
