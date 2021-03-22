//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Evaluator.h"


Yisp::Type::YispAST Yisp::Evaluator::eval_symbol(const Type::YispAST &ast, Frame &frame) {
    return frame.lookup(ast.symbol);
}

Yisp::Type::YispAST Yisp::Evaluator::eval_list(const Type::YispAST &ast, Frame &frame) {
    auto list = Type::YispAST::create_list({});
    for (const auto &item : ast.items) {
        auto value = Evaluator::eval(item, frame);
        list.items.push_back(value);
    }
    return list;
}

Yisp::Type::YispAST Yisp::Evaluator::eval_ast(const Type::YispAST &ast, Frame &frame) {
    switch (ast.type) {
        case Type::Type::Symbol:
            return eval_symbol(ast, frame);
        case Type::Type::List:
            return eval_list(ast, frame);
        default:
            return ast;
    }
}

Yisp::Type::YispAST Yisp::Evaluator::eval_definition(const Type::YispAST &ast, Frame &frame) {
    Type::YispAST name = Syntax::definition_name(ast);
    Type::YispAST value_arg = Syntax::definition_value(ast);
    Type::YispAST value = Evaluator::eval(value_arg, frame);
    frame.set(name.symbol, value);
    return value;
}

Yisp::Type::YispAST Yisp::Evaluator::eval_assignment(const Type::YispAST &ast, Frame &frame) {
    Type::YispAST name = Syntax::variable_name(ast);
    Type::YispAST update_arg = Syntax::variable_update(ast);
    Type::YispAST update = Evaluator::eval(update_arg, frame);
    frame.set(name.symbol, update);
    return update;
}

Yisp::Type::YispAST Yisp::Evaluator::eval_local_assignment(const Type::YispAST &ast, Frame &frame) {
    Frame local{std::make_shared<Frame>(frame)};
    std::vector<Type::YispAST> vars = Syntax::local_variables(ast);
    for (auto it = vars.begin(); it != vars.end(); it += 2) {
        auto name = *it;
        auto binding = *(it + 1);
        auto value = Evaluator::eval(binding, local);
        local.set(name.symbol, value);
    }
    Type::YispAST body = Syntax::local_body(ast);
    return Evaluator::eval(body, local);
}

Yisp::Type::YispAST Yisp::Evaluator::eval_if(const Type::YispAST &ast, Frame &frame) {
    Type::YispAST predicate = Syntax::if_predicate(ast);
    Type::YispAST predicate_value = Evaluator::eval(predicate, frame);
    if (predicate_value.is_true()) {
        Type::YispAST consequent = Syntax::if_consequent(ast);
        return Evaluator::eval(consequent, frame);
    } else {
        Type::YispAST alternative = Syntax::if_alternative(ast);
        return Evaluator::eval(alternative, frame);
    }
}

Yisp::Type::YispAST Yisp::Evaluator::eval_function(const Type::YispAST &ast, Frame &frame) {
    std::vector<Type::YispAST> parameters = Syntax::function_parameters(ast);
    Type::YispAST body = Syntax::function_body(ast);
    auto fn = [parameters, body, &frame](std::vector<Type::YispAST> arguments) {
        Frame local{std::make_shared<Frame>(frame)};
        if (arguments.size() != parameters.size()) {
            throw invalid_arg_size("The procedure", arguments.size(), parameters.size());
        }
        for (size_t i = 0; i < parameters.size(); i++) {
            auto parameter = parameters.at(i);
            auto argument = arguments.at(i);
            local.set(parameter.symbol, argument);
        }
        return Evaluator::eval(body, local);
    };
    return Type::YispAST::create_function(fn);
}

bool Yisp::Evaluator::is_self_evaluating(const Type::YispAST &ast) {
    return ast.is_number() || ast.is_string() || ast.is_symbol();
}


Yisp::Type::YispAST Yisp::Evaluator::eval(const Type::YispAST &ast, Frame &frame) {
    if (is_self_evaluating(ast)) {
        return eval_ast(ast, frame);
    }

    auto list = ast.items;
    if (list.empty()) {
        return ast;
    }

    auto symbol = list.front().symbol;
    if (Syntax::is_definition(symbol)) {
        return eval_definition(ast, frame);
    } else if (Syntax::is_assigment(symbol)) {
        return eval_assignment(ast, frame);
    } else if (Syntax::is_local_assignment(symbol)) {
        return eval_local_assignment(ast, frame);
    } else if (Syntax::is_if(symbol)) {
        return eval_if(ast, frame);
    } else if (Syntax::is_function(symbol)) {
        return eval_function(ast, frame);
    } else {
        Type::YispAST ast_value = eval_ast(ast, frame);
        Type::YispAST function = Syntax::apply_function(ast_value);
        std::vector<Type::YispAST> arguments{Syntax::apply_arguments(ast_value)};
        return Evaluator::apply(function, arguments);
    }
}

Yisp::Type::YispAST Yisp::Evaluator::apply(const Type::YispAST &function, const std::vector<Type::YispAST> &arguments) {
    auto result = function.lambda(arguments);
    return result;
}
