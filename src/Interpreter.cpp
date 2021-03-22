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

//void Yisp::Interpreter::repl() {
//    Frame global_frame{Frame::global()};
//    Printer::welcome();
//    std::string input;
//    while (true) {
//        Printer::prompt();
//        input = Yisp::Interpreter::getinput();
//        chrono_tp start_time = get_time_now();
//        try {
//            if (input.length() < 1) {
//                throw no_code();
//            } else if (input == "(exit)") {
//                break;
//            } else {
//                auto output = rep(input, global_frame);
//                Printer::format_print(output);
//            }
//        }
//        catch (std::runtime_error &err) {
//            std::cout << err.what() << std::endl;
//        }
//        chrono_tp end_time = get_time_now();
//        std::cout << ";Spend " << get_elapsed_msec(start_time, end_time) << " ms" << std::endl;
//    }
//}

