//
// Created by YuzukiTsuru on 2021/3/16.
//

#ifndef Interpreter_H
#define Interpreter_H

#include <iostream>
#include <vector>
#include <chrono>

#include "Yisp.h"
#include "Evaluator.h"
#include "Frame.h"
#include "Printer.h"
#include "Reader.h"

namespace Yisp {
    class Interpreter {
    public:
        explicit Interpreter(const char *file_name);

        static std::string rep(const std::string &line, Frame &frame);
    };
}

#endif // Interpreter_H
