#pragma once

class Window;
struct ImGuiContext;
using GuiImpl = ImGuiContext;

class Gui
{
public:
    Gui(Window& window);
    Gui::~Gui();

    void set_context();

private:
    GuiImpl* impl;

    Window& window;    
};