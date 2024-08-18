#include "console_view.h"

#include "imgui.h"

ConsoleView::ConsoleView(const char* name)
    : View{ name }
{
}

void ConsoleView::draw_content()
{
    ImGuiKeyChord Chord = ImGuiKey_C;
    if (ImGui::Button("Refresh") || ImGui::Shortcut(Chord))
    {
        int i = 0;
        i++;
    }
}