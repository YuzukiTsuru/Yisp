//
// Created by YuzukiTsuru on 2021/3/16.
//

#include "Interpreter.h"
#include "YispTUI.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Yisp::Frame global_frame{Yisp::Frame::global()};
        Yisp::YispTUI yispTui(global_frame);
        auto screen = Yisp::ScreenInteractive::Fullscreen();
        screen.Loop(&yispTui);
    } else if (argc == 2) {
        Yisp::Interpreter run(argv[1]);
    } else {
        return 0;
    }
}
