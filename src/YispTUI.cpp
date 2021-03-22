//
// Created by YuzukiTsuru on 2021/3/22.
//
#include <utility>

#include "YispTUI.h"

#include "Interpreter.h"
#include "Printer.h"

Yisp::YispTUI::YispTUI(Frame frame) {
    global_frame = std::move(frame);
    Add(&container);
    container.Add(&subcontainer);
    subcontainer.Add(&input_container);

    input_add.placeholder = L" Coding here, Use (exit) to exit";
    input_add.on_enter = [this] {
        input.entries.push_back(input_add.content);
        input_add.content = L"";
    };
    input_container.Add(&input_add);
    input_container.Add(&input);
}

ftxui::Element Yisp::YispTUI::Render() {
    auto input_win = window(text(L" Code "), hbox({text(L"~#: "), input_add.Render()}) | flex) | flex;
    return vbox({
                        hbox(text(L"   Welcome to Yisp   ") | border | center | color(Color::Cyan)),
                        hbox(input_win),
                        vbox(RenderCommandLine()),
                }) | border;
}

ftxui::Elements Yisp::YispTUI::RenderCommandLine() {
    Elements line;
    // Input
    for (auto &it : input.entries) {
        std::string input_code(it.begin(), it.end());
        std::string output;

        if (input_code.length() < 1) {
            output = ";No code entered.";
        } else {
            try {
                output = Printer::format_print(Interpreter::rep(input_code, global_frame));
            } catch (std::runtime_error &err) {
                output = err.what();
            }
        }
        std::wstring output_code(output.begin(), output.end());
        line.push_back(text(output_code) | color(Color::RedLight));
    }
    return line;
}
