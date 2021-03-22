//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Interpreter.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Yisp::Interpreter::repl();
    } else if (argc == 2) {
        Yisp::Interpreter run(argv[1]);
    } else {
        return 0;
    }
}
