#pragma once

#include "windows.h"

class SDL_Window;
using WindowImpl = SDL_Window;

class Window
{
public:
    Window(int width, int height);
    WindowImpl* get_impl() { return impl; }

    HWND hwnd;

private:
    WindowImpl* impl;
};