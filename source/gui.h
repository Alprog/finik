#pragma once

class Window;
struct ImGuiContext;
using GuiImpl = ImGuiContext;

class Gui
{
public:
    Gui(Window& window);
    void set_context();

private:
    GuiImpl* impl;

    Window& window;    
};