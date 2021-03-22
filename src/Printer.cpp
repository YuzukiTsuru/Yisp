//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Printer.h"

std::string Yisp::Printer::ast_to_string(const Type::YispAST &ast) {
    std::string result;
    std::string padding = " ";

    switch (ast.type) {
        case Type::Type::String:
            result = ast.string;
            break;
        case Type::Type::Number:
            result = std::to_string(ast.number);
            break;
        case Type::Type::Symbol:
            result = ast.symbol;
            break;
        case Type::Type::True:
            result = "true";
            break;
        case Type::Type::False:
            result = "false";
            break;
        case Type::Type::Nil:
            result = "nil";
            break;
        case Type::Type::Function:
            result = "#<function>";
            break;
        case Type::Type::List:
            result += "(";
            for (auto i = ast.items.begin(); i != ast.items.end(); ++i) {
                if (std::next(i) == ast.items.end()) {
                    padding = "";
                }
                result += ast_to_string(*i) + padding;
            }
            result += ")";
            break;
    }
    return result;
}

std::string Yisp::Printer::print(const Type::YispAST &ast) {
    return ast_to_string(ast);
}

std::string Yisp::Printer::format_print(const std::string &ast_str) {
    return ";Value: " + ast_str;
}