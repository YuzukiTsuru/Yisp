//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Reader.h"

std::optional<double> Yisp::Reader::token_to_number(const std::string &token) {
    // Convert all Double, determine whether it is a number
    std::optional<double> number = std::nullopt;
    if (std::all_of(token.begin(), token.end(), [](char s) { return isdigit(s); })) {
        number = std::stod(token);
    }
    return number;
}

std::string Yisp::Reader::clean(const std::string &text) {
    std::string clean = text;
    clean.erase(std::remove(clean.begin(), clean.end(), ','), clean.end());
    return clean;
}

std::vector<std::string> Yisp::Reader::split(const std::string &text, const std::string &regex_str) {
    std::regex regex{regex_str};
    std::sregex_token_iterator iter(text.begin(), text.end(), regex);
    std::sregex_token_iterator end;
    std::vector<std::string> split;
    for (; iter != end; iter++) {
        split.push_back(*iter);
    }
    return split;
}

Yisp::Type::YispAST Yisp::Reader::read(const std::string &program) {
    auto tokens = tokenize(program);
    auto reader = Reader(tokens);
    auto form = reader.read_form();
    return form;
}

std::vector<std::string> Yisp::Reader::tokenize(const std::string &text) {
    std::string cleansed_text = clean(text);
    auto tokens = split(cleansed_text, Syntax::grammar);
    return tokens;
}

Yisp::Type::YispAST Yisp::Reader::read_form() {
    std::string token = peek().value_or("");
    if (Syntax::is_list_delimited(token)) {
        return read_list();
    } else if (Syntax::is_string_delimited(token)) {
        return read_string();
    } else {
        return read_atom();
    }
}

Yisp::Type::YispAST Yisp::Reader::read_list() {
    auto list = Yisp::Type::YispAST::create_list({});
    while (next().has_value() && peek().value_or(")") != ")") {
        auto form = read_form();
        list.items.push_back(form);
    }
    if (!peek().has_value()) {
        throw std::runtime_error(";Unbalanced parentheses.");
    }
    return list;
}

Yisp::Type::YispAST Yisp::Reader::read_string() {
    std::string str = peek().value_or("");
    while (peek().value().back() != '"' && next().has_value()) {
        str += " " + peek().value();
    }
    if (str.back() != '"') {
        throw std::runtime_error(";Unbalanced string.");
    }
    str = str.substr(1, str.length() - 2); // Remove string quotes: ""
    return Yisp::Type::YispAST::create_string(str);
}

Yisp::Type::YispAST Yisp::Reader::read_atom() {
    std::string token = peek().value_or("");
    if (token_to_number(token) != std::nullopt) {
        auto num = token_to_number(token).value();
        return Yisp::Type::YispAST::create_number(num);
    } else if (token == Type::types[Yisp::Type::Type::True]) {
        return Yisp::Type::YispAST::create_true();
    } else if (token == Type::types[Yisp::Type::Type::False]) {
        return Yisp::Type::YispAST::create_false();
    } else if (token == Type::types[Yisp::Type::Type::Nil]) {
        return Yisp::Type::YispAST::create_nil();
    } else {
        return Yisp::Type::YispAST::create_symbol(token);
    }
}

std::optional<std::string> Yisp::Reader::next() {
    if (out_of_bounds()) {
        return std::nullopt;
    }
    return tokens.at(position++);
}

std::optional<std::string> Yisp::Reader::peek() {
    if (out_of_bounds()) {
        return std::nullopt;
    }
    return tokens.at(position);
}

bool Yisp::Reader::out_of_bounds() {
    return position >= tokens.size();
}
