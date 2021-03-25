//
// Created by Ghost Gloomy on 2021/3/25.
//

#ifndef YISP_REPL_H
#define YISP_REPL_H

#include <iostream>
#include <chrono>

namespace Yisp {
    class Repl {
    public:
        static void repl();

    private:
        using chrono_tp = std::chrono::system_clock::time_point;

        static std::string getinput();

        static double get_elapsed_msec(chrono_tp st, chrono_tp end);

        static chrono_tp get_time_now();
    };
}


#endif //YISP_REPL_H
