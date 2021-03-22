//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

#include "Yisp.h"

class unbound_symbol_error : public std::runtime_error {
public:
    explicit unbound_symbol_error(const std::string &what) : std::runtime_error(";Unbound symbol: " + what + ".") {};
};

class ill_form_error : public std::runtime_error {
public:
    explicit ill_form_error(const std::string &what) : std::runtime_error(";Ill formed special: " + what + ".") {};
};

class invalid_arg_size : public std::runtime_error {
public:
    invalid_arg_size(const std::string &name, size_t size, size_t expected_size) : std::runtime_error(
            "; " + name + " has been called with " + std::to_string(size) + " arguments; it requires " + std::to_string(expected_size) + ".") {};
};

class no_code : public std::runtime_error {
public:
    explicit no_code(const std::string &what) : std::runtime_error(";No code entered: " + what + ".") {};
};

#endif // EXCEPTION_H
