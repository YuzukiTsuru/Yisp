//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef YISPTYPE_H
#define YISPTYPE_H

#include <functional>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Yisp.h"

namespace Yisp::Type {

    // TODO: 使用bool代替True False
    enum class Type {
        Nil,
        True,
        False,
        Number,
        String,
        List,
        Symbol,
        Function
    };

    static std::unordered_map<Type, std::string> types = { /* NOLINT */
            {Type::Nil,      "nil"},
            {Type::True,     "true"},
            {Type::False,    "false"},
            {Type::Number,   "number"},
            {Type::String,   "string"},
            {Type::List,     "list"},
            {Type::Symbol,   "symbol"},
            {Type::Function, "function"}
    };

    struct YispAST {
        Type type = Type::Nil;
        double number = 0.0;
        std::string symbol;
        std::string string;
        std::vector<YispAST> items;
        std::function<YispAST(std::vector<YispAST>)> lambda;

        [[nodiscard]] bool is_number() const;

        [[nodiscard]] bool is_string() const;

        [[nodiscard]] bool is_symbol() const;

        [[nodiscard]] bool is_list() const;

        [[nodiscard]] bool is_true() const;

        [[nodiscard]] bool is_false() const;

        [[nodiscard]] bool is_function() const;

        [[nodiscard]] bool is_nil() const;

        static YispAST create_nil();

        static YispAST create_number(double number);

        static YispAST create_string(const std::string &string);

        static YispAST create_symbol(const std::string &symbol);

        static YispAST create_list(const std::vector<YispAST> &list);

        static YispAST create_function(std::function<YispAST(std::vector<YispAST>)> function);

        static YispAST create_true();

        static YispAST create_false();
    };
}

#endif // YISPTYPE_H
