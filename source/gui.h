#pragma once

class Window;
struct ImGuiContext;
using GuiImpl = ImGuiContext;

struct ID3D12GraphicsCommandList;

class Gui
{
public:
    Gui(Window& window);
    Gui::~Gui();

    void prepare();
    void render(ID3D12GraphicsCommandList* command_list);
    void set_context();

private:
    GuiImpl* impl;
    Window& window;    
};