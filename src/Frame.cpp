//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Frame.h"

void Yisp::Frame::set(const std::string &sym, const Yisp::Type::YispAST &value) {
    symbols[sym] = value;
}

Yisp::Type::YispAST Yisp::Frame::lookup(const std::string &sym) const {
    std::optional<Frame> opt{find(sym)};
    if (opt.has_value()) {
        auto frame = opt.value();
        return frame.symbols[sym];
    } else {
        throw unbound_symbol_error(sym);
    }
}

std::optional<Yisp::Frame> Yisp::Frame::find(const std::string &sym) const {
    bool found = symbols.find(sym) != symbols.end();
    if (found) {
        return *this;
    } else if (parent != nullptr) {
        return parent->find(sym);
    } else {
        return std::nullopt;
    }
}

[[maybe_unused]] void Yisp::Frame::print_symbols() const {
    for (const auto&[sym, _] : symbols) {
        std::cout << sym << std::endl;
    }
}

Yisp::Frame Yisp::Frame::global() {
    Frame global;
    for (const auto&[sym, op] : core) {
        auto function = Yisp::Type::YispAST::create_function(op);
        global.set(sym, function);
    }
    return global;
}

