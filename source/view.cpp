#include "view.h"

#include "imgui.h"

View::View(const char* name)
    : name{name}
{
}

void View::draw()
{
    ImGui::Begin(name);
    draw_content();
    ImGui::End();
}