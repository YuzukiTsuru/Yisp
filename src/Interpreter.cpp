//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Interpreter.h"

#include "FileIO.h"

Yisp::Interpreter::Interpreter(const char *file_name) {
    Frame global_frame{Frame::global()};
    std::string code_from_file = FileIO::read_from_file(file_name);
    try {
        if (code_from_file.length() < 1) {
            throw no_code();
        } else {
            auto output = rep(code_from_file, global_frame);
            Printer::format_print(output);
        }
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }
}

std::string Yisp::Interpreter::rep(const std::string &line, Frame &frame) {
    auto expression = Yisp::Reader::read(line);
    auto value = Evaluator::eval(expression, frame);
    auto output = Printer::print(value);
    return output;
}

