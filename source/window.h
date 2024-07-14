#pragma once

#include "windows.h"
#include "stdint.h"

class SDL_Window;
using WindowImpl = SDL_Window;

class SwapChain;
class Scene;
class Gui;

class Window
{
public:
    Window(int width, int height);
    ~Window();

    void renderScene();

    WindowImpl* get_impl() { return impl; }

    uint32_t id;
    HWND hwnd;
    SwapChain* swap_chain;
    Scene* scene;
    Gui* gui;

private:
    WindowImpl* impl;
};