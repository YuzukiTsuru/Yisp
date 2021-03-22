//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "Yisp.h"
#include "exception.h"
#include "Operators.h"
#include "Type.h"

namespace Yisp {
    class Frame {
    public:
        Frame() = default;

        explicit Frame(std::shared_ptr<Frame> parent) : parent(std::move(parent)) {};

        [[nodiscard]] Type::YispAST lookup(const std::string &sym) const;

        void set(const std::string &sym, const Type::YispAST &value);

        [[maybe_unused]] void print_symbols() const;

        static Frame global();

    private:
        [[nodiscard]] std::optional<Frame> find(const std::string &sym) const;

        std::shared_ptr<Frame> parent;

        std::unordered_map<std::string, Type::YispAST> symbols;
    };
}
#endif // FRAME_H
