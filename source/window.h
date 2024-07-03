#pragma once

#include "windows.h"
#include "stdint.h"

class SDL_Window;
using WindowImpl = SDL_Window;

class Gui;

class Window
{
public:
    Window(int width, int height);
    ~Window();

    WindowImpl* get_impl() { return impl; }

    uint32_t id;
    HWND hwnd;
    Gui* gui;

private:
    WindowImpl* impl;
};