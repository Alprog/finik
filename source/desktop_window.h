#pragma once

#include "windows.h"
#include "stdint.h"

class SDL_Window;
using WindowImpl = SDL_Window;

class SwapChain;
class Scene;
class Gui;

class DesktopWindow
{
public:
    DesktopWindow(int width, int height);
    ~DesktopWindow();

    void renderScene();

    WindowImpl* get_impl() { return impl; }

    uint32_t id;
    HWND hwnd;
    SwapChain* swap_chain;
    Scene* scene;
    Gui* gui;

    int width;
    int height;

private:
    WindowImpl* impl;
};