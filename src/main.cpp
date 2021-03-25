//
// Created by YuzukiTsuru on 2021/3/16.
//

#include <iostream>

#include <argparse/argparse.hpp>

#include "Repl.h"
#include "YispTUI.h"
#include "Interpreter.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Yisp::Frame global_frame{Yisp::Frame::global()};
        Yisp::YispTUI yispTui(global_frame);
        auto screen = Yisp::ScreenInteractive::Fullscreen();
        screen.Loop(&yispTui);
    } else if (argc == 2) {
        argparse::ArgumentParser program("Yisp");

        program.add_argument("-t", "--tui").help("Disable file input and TUI for Debug.")
                .default_value(false)
                .implicit_value(true);

        try {
            program.parse_args(argc, argv);
        }
        catch (const std::runtime_error &err) {
            std::cout << err.what() << std::endl;
            std::cout << program;
            exit(0);
        }

        if (program["-t"] == false) {
            Yisp::Interpreter run(argv[1]);
        } else {
            Yisp::Repl::repl();
        }
    } else {
        return 0;
    }
}
