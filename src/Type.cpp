//
// Created by YuzukiTsuru on 2021/3/19.
//

#include "Type.h"

bool Yisp::Type::YispAST::is_number() const {
    return type == Type::Number;
}

bool Yisp::Type::YispAST::is_string() const {
    return type == Type::String;
}

bool Yisp::Type::YispAST::is_symbol() const {
    return type == Type::Symbol;
}

bool Yisp::Type::YispAST::is_list() const {
    return type == Type::List;
}

bool Yisp::Type::YispAST::is_true() const {
    return type == Type::True;
}

bool Yisp::Type::YispAST::is_false() const {
    return type == Type::False;
}

bool Yisp::Type::YispAST::is_function() const {
    return type == Type::Function;
}

bool Yisp::Type::YispAST::is_nil() const {
    return type == Type::Nil;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_nil() {
    YispAST exp{.type = Type::Nil};
    return exp;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_number(double number) {
    YispAST exp{.type = Type::Number, .number = number};
    return exp;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_string(const std::string &string) {
    YispAST exp{.type = Type::String, .string = string};
    return exp;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_symbol(const std::string &symbol) {
    YispAST exp{.type = Type::Symbol, .symbol = symbol};
    return exp;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_list(const std::vector<YispAST> &list) {
    YispAST exp{.type = Type::List, .items = list};
    return exp;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_function(std::function<YispAST(std::vector<YispAST>)> function) {
    YispAST exp{.type = Type::Function, .lambda = std::move(function)};
    return exp;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_true() {
    YispAST t{.type = Type::True};
    return t;
}

Yisp::Type::YispAST Yisp::Type::YispAST::create_false() {
    YispAST f{.type = Type::False};
    return f;
}

