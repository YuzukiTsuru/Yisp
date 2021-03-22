//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Interpreter.h"

Yisp::Interpreter::Interpreter(const char *file_name) {
    // TODO: 增加文件输入
    file_name_string = file_name;

}

std::string Yisp::Interpreter::getinput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

std::string Yisp::Interpreter::rep(const std::string &line, Frame &frame) {
    auto expression = Yisp::Reader::read(line);
    auto value = Evaluator::eval(expression, frame);
    auto output = Printer::print(value);
    return output;
}

void Yisp::Interpreter::repl() {
    Frame global_frame{Frame::global()};
    Printer::welcome();
    std::string input;
    while (true) {
        Printer::prompt();
        input = Yisp::Interpreter::getinput();
        chrono_tp start_time = get_time_now();
        try {
            if (input.length() < 1) {
                throw no_code("No code entered");
            } else if (input == "(exit)") {
                break;
            } else {
                auto output = Yisp::Interpreter::rep(input, global_frame);
                Printer::format_print(output);
            }
        }
        catch (std::runtime_error &err) {
            std::cout << err.what() << std::endl;
        }
        chrono_tp end_time = get_time_now();
        std::cout << ";Spend " << get_elapsed_msec(start_time, end_time) << " ms" << std::endl;
    }
}

double Yisp::Interpreter::get_elapsed_msec(Yisp::Interpreter::chrono_tp st, Yisp::Interpreter::chrono_tp end) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - st).count() / 1.0e6;
}

Yisp::Interpreter::chrono_tp Yisp::Interpreter::get_time_now() {
    return std::chrono::system_clock::now();
}

