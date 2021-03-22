//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Syntax.h"

[[maybe_unused]] bool Yisp::Syntax::is_comment_delimited(const std::string &token) {
    return token.at(0) == delimiters[DelimiterKind::comment];
}

bool Yisp::Syntax::is_list_delimited(const std::string &token) {
    return token.at(0) == delimiters[DelimiterKind::list];
}

bool Yisp::Syntax::is_string_delimited(const std::string &token) {
    return token.at(0) == delimiters[DelimiterKind::string];
}

bool Yisp::Syntax::out_of_bounds(size_t index, size_t size) {
    return index >= size;
}

bool Yisp::Syntax::is_definition(const std::string &symbol) {
    return symbol == keywords[KeywordKind::definition];
}

Yisp::Type::YispAST Yisp::Syntax::definition_name(const Type::YispAST &expression) {
    // name_pos: 1
    // (def <name> <value>)
    // _^___^______^______
    //  0   1      2
    size_t name_pos = 1;
    if (out_of_bounds(name_pos, expression.items.size())) {
        throw ill_form_error("missing definition name\n\n"
                             "(def <name> <value>)\n"
                             "_____^______________");
    }
    return expression.items.at(name_pos);
}

Yisp::Type::YispAST Yisp::Syntax::definition_value(const Type::YispAST &expression) {
    // def_pos: 2
    // (def <name> <value>)
    // _^___^______^_______
    //  0   1      2
    size_t value_pos = 2;
    if (out_of_bounds(value_pos, expression.items.size())) {
        throw ill_form_error("missing definition value\n\n"
                             "(def <name> <value>)\n"
                             "____________^_______");
    }
    return expression.items.at(value_pos);
}

// Assignment Selectors
bool Yisp::Syntax::is_assigment(const std::string &symbol) {
    return symbol == keywords[KeywordKind::assignment];
}

Yisp::Type::YispAST Yisp::Syntax::variable_name(const Type::YispAST &expression) {
    // name_pos: 1
    // (set <name> <update>)
    // _^___^______^________
    //  0   1      2
    size_t name_pos = 1;
    if (out_of_bounds(name_pos, expression.items.size())) {
        throw ill_form_error("missing variable name\n\n"
                             "(set <name> <update>)\n"
                             "_____^_______________");
    }
    return expression.items.at(name_pos);
}

Yisp::Type::YispAST Yisp::Syntax::variable_update(const Type::YispAST &expression) {
    // update_pos: 2
    // (set <name> <update>)
    // _^___^______^________
    //  0   1      2
    size_t update_pos = 2;
    if (out_of_bounds(update_pos, expression.items.size())) {
        throw ill_form_error("missing variable update\n\n"
                             "(set <name> <update>)\n"
                             "____________^________");
    }
    return expression.items.at(update_pos);
}

// Local Assignment Selectors

bool Yisp::Syntax::is_local_assignment(const std::string &symbol) {
    return symbol == keywords[KeywordKind::local_assignment];
}

std::vector<Yisp::Type::YispAST> Yisp::Syntax::local_variables(const Type::YispAST &expression) {
    // variables_pos: 1
    // (let (<name> <value>) <body>)
    // _^___^________________^______
    //  0   1                2
    size_t variables_pos = 1;
    if (out_of_bounds(variables_pos, expression.items.size())) {
        throw ill_form_error("missing local names.\n\n"
                             "(let (<name> <value>) <body>)\n"
                             "_____^_______________________");
    }
    auto variables = expression.items.at(variables_pos);
    return variables.items;
}

Yisp::Type::YispAST Yisp::Syntax::local_body(const Type::YispAST &expression) {
    // body_pos: 2
    // (let (<name> <value>) <body>)
    // _^___^________________^______
    //  0   1                2
    size_t body_pos = 2;
    if (out_of_bounds(body_pos, expression.items.size())) {
        throw ill_form_error("missing local assignment body.\n\n"
                             "(let (<name> <value>) <body>)\n"
                             "______________________^______");
    }
    return expression.items.at(body_pos);
}

// Function Selectors

bool Yisp::Syntax::is_function(const std::string &symbol) {
    return symbol == keywords[KeywordKind::function];
}

std::vector<Yisp::Type::YispAST> Yisp::Syntax::function_parameters(const Type::YispAST &expression) {
    // parameters_pos: 1
    // (fn  (<parameters>) <body>)
    // _^___^______________^______
    //  0   1              2
    size_t parameters_pos = 1;
    if (out_of_bounds(parameters_pos, expression.items.size())) {
        throw ill_form_error("missing function paramters.\n\n"
                             "(fn (<parameters>) <body>)\n"
                             "____^_____________________");
    }
    auto parameters = expression.items.at(parameters_pos);
    return parameters.items;
}

Yisp::Type::YispAST Yisp::Syntax::function_body(const Type::YispAST &expression) {
    // body_pos: 2
    // (fn  (<parameters>) <body>)
    // _^___^______________^______
    //  0   1              2
    size_t body_pos = 2;
    if (out_of_bounds(body_pos, expression.items.size())) {
        throw ill_form_error("missing function body.\n\n"
                             "(fn (<parameters>) <body>)\n"
                             "___________________^______");
    }
    return expression.items.at(body_pos);
}

// Apply Selectors

Yisp::Type::YispAST Yisp::Syntax::apply_function(const Type::YispAST &expression) {
    // function_pos: 0 (front)
    // (<function-name> <arg-1> ... <arg-n>)
    // _^_______________^___________^_______
    //  0               1           n
    auto function = expression.items.front();
    if (!function.is_function()) {
        throw ill_form_error("object is not callable");
    }
    return function;
}

std::vector<Yisp::Type::YispAST>Yisp::Syntax::apply_arguments(const Type::YispAST &expression) {
    // arguments_pos: [1, n]
    // (<function-name> <arg-1> ... <arg-n>)
    // _^_______________^___________^_______
    //  0               1           n
    // TODO: Make sure number operands are same as error_explanation's expected?
    std::vector<Type::YispAST> l{expression.items};
    std::vector<Type::YispAST> arguments{l.begin() + 1, l.end()};
    return arguments;
}

// If Selectors

bool Yisp::Syntax::is_if(const std::string &symbol) {
    return symbol == keywords[KeywordKind::conditional_if];
}

Yisp::Type::YispAST Yisp::Syntax::if_predicate(const Type::YispAST &expression) {
    // predicate_pos: 1
    // (if (<predicate>) <consequent> <?-alternative>)
    // _^___^____________^____________^_____________
    //  0   1            2            3
    size_t predicate_pos = 1;
    if (out_of_bounds(predicate_pos, expression.items.size())) {
        throw ill_form_error(
                "missing predicate.\n\n"
                "(if (<predicate>) <consequent> <?-alternative>)\n"
                "_____^_________________________________________");
    }
    return expression.items.at(predicate_pos);
}

Yisp::Type::YispAST Yisp::Syntax::if_consequent(const Type::YispAST &expression) {
    // consequent_pos: 2
    // (if (<predicate>) <consequent> <?-alternative>)
    // _^___^____________^____________^______________
    //  0   1            2            3
    size_t consequent_pos = 2;
    if (out_of_bounds(consequent_pos, expression.items.size())) {
        throw ill_form_error(
                "missing consequent.\n\n"
                "(if (<predicate>) <consequent> <?-alternative>)\n"
                "__________________^____________________________");
    }
    return expression.items.at(consequent_pos);
}

Yisp::Type::YispAST Yisp::Syntax::if_alternative(const Type::YispAST &expression) {
    size_t alternative_pos = 3;
    if (expression.items.size() < 4) {
        return Type::YispAST::create_nil();
    }
    return expression.items.at(alternative_pos);
}