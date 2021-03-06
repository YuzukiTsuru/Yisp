#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/string.hpp"

using namespace ftxui;

class YispTUI : public Component {
public:
    YispTUI() {
        Add(&container);
        container.Add(&subcontainer);

        // Input    ----------------------------------------------------------------
        subcontainer.Add(&input_container);

        input_add.placeholder = L" Coding here, Use (exit) to exit";
        input_add.on_enter = [this] {
            input.entries.push_back(input_add.content);
            input_add.content = L"";
        };
        input_container.Add(&input_add);
        input_container.Add(&input);
    }

    ~YispTUI() override = default;

    Element Render() override {
        auto input_win = window(text(L" Code "), hbox({text(L"~#: "), input_add.Render()}) | flex) | flex;
        return vbox({
                            hbox(text(L"   Welcome to Yisp   ") | border | center | flex | color(Color::Cyan)),
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

private:
    Container container = Container::Horizontal();
    Container subcontainer = Container::Vertical();
    Container input_container = Container::Horizontal();
    Input input_add;
    Menu input;
};

int main(int argc, const char *argv[]) {
    auto screen = ScreenInteractive::Fullscreen();
    YispTUI tab;
    screen.Loop(&tab);
    return 0;
}