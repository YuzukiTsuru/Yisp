//
// Created by YuzukiTsuru on 2021/3/22.
//

#ifndef YISP_YISPTUI_H
#define YISP_YISPTUI_H

#include "Frame.h"

#include "ftxui/component/checkbox.hpp"
#include "ftxui/component/container.hpp"
#include "ftxui/component/input.hpp"
#include "ftxui/component/menu.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/string.hpp"

namespace Yisp {
    using namespace ftxui;

    class YispTUI : public Component {
    public:
        explicit YispTUI(Frame frame);

        ~YispTUI() override = default;

    private:
        Container container = Container::Horizontal();
        Container subcontainer = Container::Vertical();
        Container input_container = Container::Horizontal();
        Input input_add;
        Menu input;
        Frame global_frame;

        Element Render() override;

        Elements RenderCommandLine();
    };
}
#endif //YISP_YISPTUI_H
