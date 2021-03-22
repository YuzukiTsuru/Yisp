//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef OPERATORS_H
#define OPERATORS_H

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Yisp.h"
#include "exception.h"
#include "Printer.h"
#include "Type.h"

namespace Yisp {
    class Operators {
    public:
        // Arithmetic
        static Type::YispAST add(const std::vector<Type::YispAST> &args);

        static Type::YispAST sub(std::vector<Type::YispAST> args);

        static Type::YispAST mul(const std::vector<Type::YispAST> &args);

        static Type::YispAST div(std::vector<Type::YispAST> args);

        // I/O
        static Type::YispAST print(std::vector<Type::YispAST> args);

        // List Processing
        static Type::YispAST list(const std::vector<Type::YispAST> &args);

        static Type::YispAST is_empty(std::vector<Type::YispAST> args);

        static Type::YispAST count(std::vector<Type::YispAST> args);

        static Type::YispAST first(std::vector<Type::YispAST> args);

        static Type::YispAST rest(std::vector<Type::YispAST> args);

        // Logical
        // Note: `_` prefix to avoid C++ keyword clash.
        static Type::YispAST _not(std::vector<Type::YispAST> args);

        static Type::YispAST _and(const std::vector<Type::YispAST> &args);

        static Type::YispAST _or(const std::vector<Type::YispAST> &args);

        // Relational
        static Type::YispAST less(std::vector<Type::YispAST> args);

        static Type::YispAST less_eq(std::vector<Type::YispAST> args);

        static Type::YispAST greater(std::vector<Type::YispAST> args);

        static Type::YispAST greater_eq(std::vector<Type::YispAST> args);

        static Type::YispAST equal(std::vector<Type::YispAST> args);

        static Type::YispAST not_equal(std::vector<Type::YispAST> args);

        // type Predicates
        static Type::YispAST is_list(std::vector<Type::YispAST> args);

        static Type::YispAST is_nil(std::vector<Type::YispAST> args);

        static Type::YispAST is_true(std::vector<Type::YispAST> args);

        static Type::YispAST is_false(std::vector<Type::YispAST> args);

        static Type::YispAST is_symbol(std::vector<Type::YispAST> args);

        static Type::YispAST is_number(std::vector<Type::YispAST> args);

    private:
        static Type::YispAST equal_helper(const Type::YispAST &l1, const Type::YispAST &l2);
    };

    using CoreOperator = std::function<Type::YispAST(std::vector<Type::YispAST>)>;
    // Core Operator Table
    static std::unordered_map<std::string, CoreOperator> core = { /*NOLINT*/
            // Arithmetic
            {"+",       &Operators::add},
            {"-",       &Operators::sub},
            {"*",       &Operators::mul},
            {"/",       &Operators::div},
            // I/0
            {"print",   &Operators::print},
            // List Processing
            {"list",    &Operators::list},
            {"empty?",  &Operators::is_empty},
            {"count",   &Operators::count},
            {"first",   &Operators::first},
            {"rest",    &Operators::rest},
            // Logical
            {"not",     &Operators::_not},
            {"and",     &Operators::_and},
            {"or",      &Operators::_or},
            // Relational
            {"<",       &Operators::less},
            {"<=",      &Operators::less_eq},
            {">",       &Operators::greater},
            {">=",      &Operators::greater_eq},
            {"=",       &Operators::equal},
            {"!=",      &Operators::not_equal},
            // type Predicates
            {"list?",   &Operators::is_list},
            {"nil?",    &Operators::is_nil},
            {"true?",   &Operators::is_true},
            {"false?",  &Operators::is_false},
            {"symbol?", &Operators::is_symbol},
            {"number?", &Operators::is_number}};
}

#endif // OPERATORS_H
