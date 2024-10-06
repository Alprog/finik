#pragma once

import std;
import view;

class DesktopWindow;
struct ImGuiContext;
using GuiImpl = ImGuiContext;

struct ID3D12GraphicsCommandList;

class Gui
{
public:
    Gui(DesktopWindow& window);
    Gui::~Gui();

    void prepare();
    void render(ID3D12GraphicsCommandList* command_list);
    void set_context();

private:
    GuiImpl* impl;
    DesktopWindow& window;

public:
    std::vector<std::unique_ptr<View>> views;
};