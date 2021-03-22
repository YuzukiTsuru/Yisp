//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Operators.h"


// Arithmetic
/// (+ <atom-1> ... <atom-n>) -> Yisp::type::YispAST.Number
Yisp::Type::YispAST Yisp::Operators::add(const std::vector<Yisp::Type::YispAST> &args) {
    auto sum = 0.0;
    for (const auto &arg : args) {
        sum += arg.number;
    }
    return Yisp::Type::YispAST::create_number(sum);
}

/// (- <atom-1> ... <atom-n>) -> Yisp::type::YispAST.Number
Yisp::Type::YispAST Yisp::Operators::sub(std::vector<Yisp::Type::YispAST> args) {
    if (args.empty()) {
        throw std::invalid_argument("\n;NaN. 0 arguments given.\n");
    }
    if (args.size() == 1) {
        auto num = args.at(0).number;
        return Yisp::Type::YispAST::create_number(num * -1);
    }
    auto diff = args.at(0).number;
    for (auto it = args.begin() + 1; it != args.end(); it++) {
        diff -= it->number;
    }
    return Yisp::Type::YispAST::create_number(diff);
}

/// (* <atom-1> ... <atom-n>) -> Yisp::type::YispAST.Number
Yisp::Type::YispAST Yisp::Operators::mul(const std::vector<Yisp::Type::YispAST> &args) {
    auto prod = 1.0;
    for (const auto &arg : args) {
        prod *= arg.number;
    }
    return Yisp::Type::YispAST::create_number(prod);
}

/// (/ <atom-1> ... <atom-n>) -> Yisp::type::YispAST.Number
Yisp::Type::YispAST Yisp::Operators::div(std::vector<Yisp::Type::YispAST> args) {
    if (args.empty()) {
        throw std::runtime_error("\n;NaN. 0 arguments given.\n");
    }
    if (args.size() == 1) {
        auto num = args.at(0).number;
        return Yisp::Type::YispAST::create_number(1.0 / num);
    }
    auto quotient = args.at(0).number;
    for (auto it = args.begin() + 1; it != args.end(); it++) {
        if (it->number == 0) {
            throw std::runtime_error("\n;Infinity. Division by zero.\n");
        }
        quotient /= it->number;
    }
    return Yisp::Type::YispAST::create_number(quotient);
}

// I/O

/// (print <any>) -> Yisp::type::YispAST.Nil
Yisp::Type::YispAST Yisp::Operators::print(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(print <any>)", 1, args.size());
    }
    std::cout << Printer::print(args.at(0));
    return Yisp::Type::YispAST::create_nil();
}

// List Processing
// (list <atom-1 | list-1> ... <atom-n | list-n> ) -> Yisp::type::YispAST.List
Yisp::Type::YispAST Yisp::Operators::list(const std::vector<Yisp::Type::YispAST> &args) {
    return Yisp::Type::YispAST::create_list(args);
}

/// (empty? <list>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_empty(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(empty? <list>)", 1, args.size());
    }
    auto list = args.front();
    return list.items.empty() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (count <list>) -> Yisp::type::YispAST.Number
Yisp::Type::YispAST Yisp::Operators::count(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(count <list>)", 1, args.size());
    }
    auto list = args.front();
    auto count = list.items.size();
    return Yisp::Type::YispAST::create_number(static_cast<double>(count)); // (size_t -> double) cast
}

/// (first <list>) -> Yisp::type::YispAST
Yisp::Type::YispAST Yisp::Operators::first(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(first <list>)", 1, args.size());
    }

    auto list = args.front();
    if (list.items.empty()) {
        throw std::runtime_error("\n;Empty List. Cannot return the (first <list>) element.\n");
    }
    return list.items.front();
}

/// (rest <list>) -> (list Yisp::type::YispAST)
Yisp::Type::YispAST Yisp::Operators::rest(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(rest <list>)", 1, args.size());
    }

    auto list = args.front();
    if (list.items.empty()) {
        throw std::runtime_error("\n;Empty List. Cannot return the (rest <list>) of the elements.\n");
    }
    if (list.items.size() == 1) {
        return Yisp::Type::YispAST::create_list({});
    }
    std::vector<Yisp::Type::YispAST> rest{list.items.begin() + 1, list.items.end()};
    return Yisp::Type::YispAST::create_list(rest);
}

// Logical

/// (not <any>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::_not(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(not <list>)", args.size(), 1);
    }
    return (args.front().type == Yisp::Type::Type::False) ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (and <bool-1> ... <bool-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::_and(const std::vector<Yisp::Type::YispAST> &args) {
    for (const auto &arg : args) {
        if (arg.is_false()) {
            return Yisp::Type::YispAST::create_false();
        }
    }
    return Yisp::Type::YispAST::create_true();
}

/// (and <bool-1> ... <bool-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::_or(const std::vector<Yisp::Type::YispAST> &args) {
    for (const auto &arg : args) {
        if (arg.is_true()) {
            return Yisp::Type::YispAST::create_true();
        }
    }
    return Yisp::Type::YispAST::create_false();
}

// Relational

/// (< <atom-1> ... <atom-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::less(std::vector<Yisp::Type::YispAST> args) {
    for (auto it = args.begin(); it != args.end() - 1; it++) {
        if (it->number >= (it + 1)->number) {
            return Yisp::Type::YispAST::create_false();
        }
    }
    return Yisp::Type::YispAST::create_true();
}

/// (<= <atom-1> ... <atom-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::less_eq(std::vector<Yisp::Type::YispAST> args) {
    for (auto it = args.begin(); it != args.end() - 1; it++) {
        if (it->number > (it + 1)->number) {
            return Yisp::Type::YispAST::create_false();
        }
    }
    return Yisp::Type::YispAST::create_true();
}

/// (> <atom-1> ... <atom-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::greater(std::vector<Yisp::Type::YispAST> args) {
    for (auto it = args.begin(); it != args.end() - 1; it++) {
        if (it->number <= (it + 1)->number) {
            return Yisp::Type::YispAST::create_false();
        }
    }
    return Yisp::Type::YispAST::create_true();
}

/// (>= <atom-1> ... <atom-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::greater_eq(std::vector<Yisp::Type::YispAST> args) {
    for (auto it = args.begin(); it != args.end() - 1; it++) {
        if (it->number < (it + 1)->number) {
            return Yisp::Type::YispAST::create_false();
        }
    }
    return Yisp::Type::YispAST::create_true();
}

/// (= <atom-1> ... <atom-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::equal(std::vector<Yisp::Type::YispAST> args) {
    for (auto it = args.begin(); it != args.end() - 1; it++) {
        Yisp::Type::YispAST eq = equal_helper(*it, *(it + 1));
        if (eq.is_false()) {
            return Yisp::Type::YispAST::create_false();
        }
    }
    return Yisp::Type::YispAST::create_true();
}

/// (!= <atom-1> ... <atom-n>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::not_equal(std::vector<Yisp::Type::YispAST> args) {
    return _not({equal(std::move(args))});
}

// Yisp::type::type Predicates
/// (list? <list>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_list(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(list? <list>)", 1, args.size());
    }
    auto list = args.front();
    return list.is_list() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (nil? <any>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_nil(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(nil? <any>)", 1, args.size());
    }
    auto any = args.front();
    return any.is_nil() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (true? <any>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_true(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(true? <any>)", 1, args.size());
    }
    auto any = args.front();
    return any.is_true() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (false? <any>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_false(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(false? <any>)", 1, args.size());
    }
    auto any = args.front();
    return any.is_false() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (symbol? <any>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_symbol(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(symbol? <any>)", 1, args.size());
    }
    auto any = args.front();
    return any.is_symbol() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

/// (number? <any>) -> Yisp::type::YispAST.True | Yisp::type::YispAST.False
Yisp::Type::YispAST Yisp::Operators::is_number(std::vector<Yisp::Type::YispAST> args) {
    if (args.size() != 1) {
        throw invalid_arg_size("(number? <any>)", 1, args.size());
    }
    auto any = args.front();
    return any.is_number() ? Yisp::Type::YispAST::create_true() : Yisp::Type::YispAST::create_false();
}

Yisp::Type::YispAST Yisp::Operators::equal_helper(const Yisp::Type::YispAST &l1, const Yisp::Type::YispAST &l2) {
    if (l1.type != l2.type) {
        return Type::YispAST::create_false();
    }
    switch (l1.type) {
        case Type::Type::Number:
            return (l1.number == l2.number) ? Type::YispAST::create_true() : Type::YispAST::create_false();
        case Type::Type::String:
            return (l1.string == l2.string) ? Type::YispAST::create_true() : Type::YispAST::create_false();
        case Type::Type::List:
            for (unsigned long i = 0; i < l1.items.size(); i++) {
                auto predicate = equal_helper(l1.items[i], l2.items[i]);
                if (predicate.is_false()) {
                    return Type::YispAST::create_false();
                }
            }
            return Type::YispAST::create_true();
        default:
            return Type::YispAST::create_false();
    }
}
