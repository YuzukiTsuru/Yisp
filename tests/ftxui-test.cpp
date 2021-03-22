#include <cmath>
#include <thread>

#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/radiobox.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/toggle.hpp"
#include "ftxui/screen/string.hpp"

using namespace ftxui;

class CompilerComponent : public Component {
    Container container = Container::Horizontal();
    Container subcontainer = Container::Vertical();
    Container input_container = Container::Horizontal();
    Input input_add;
    Menu input;

public:
    ~CompilerComponent() override {}

    CompilerComponent() {
        Add(&container);
        container.Add(&subcontainer);

        // Input    ----------------------------------------------------------------
        subcontainer.Add(&input_container);

        input_add.placeholder = L"input files";
        input_add.on_enter = [this] {
            input.entries.push_back(input_add.content);
            input_add.content = L"";
        };
        input_container.Add(&input_add);
        input_container.Add(&input);
    }

    Element Render() override {
        auto input_win = window(text(L"Code"), hbox({text(L"~#: "), input_add.Render()}) | flex) | flex;
        return vbox({
            hbox(text(L"    Welcome to Yisp, Use (exit) to exit   ") | border | center | flex | color(Color::Cyan)),
            hbox(input_win),
            hflow(RenderCommandLine()),
        }) | border;
    }

    Elements RenderCommandLine() {
        Elements line;
        // Input
        for (auto &it : input.entries) {
            line.push_back(text(L" " + it) | color(Color::RedLight));
        }
        return line;
    }
};

int main(int argc, const char *argv[]) {
    auto screen = ScreenInteractive::Fullscreen();

    std::thread update([&screen]() {
        for (;;) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);
            screen.PostEvent(Event::Custom);
        }
    });

    CompilerComponent tab;
    screen.Loop(&tab);

    return 0;
}