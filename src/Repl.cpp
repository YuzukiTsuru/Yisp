//
// Created by Ghost Gloomy on 2021/3/25.
//


#include "Repl.h"

#include "Frame.h"
#include "exception.h"
#include "Interpreter.h"

std::string Yisp::Repl::getinput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void Yisp::Repl::repl() {
    Frame global_frame{Frame::global()};
    Printer::welcome();
    std::string input;
    while (true) {
        Printer::prompt();
        input = getinput();
        chrono_tp start_time = get_time_now();
        try {
            if (input.length() < 1) {
                throw no_code();
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

double Yisp::Repl::get_elapsed_msec(Yisp::Repl::chrono_tp st, Yisp::Repl::chrono_tp end) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - st).count() / 1.0e6;
}

Yisp::Repl::chrono_tp Yisp::Repl::get_time_now() {
    return std::chrono::system_clock::now();
}
