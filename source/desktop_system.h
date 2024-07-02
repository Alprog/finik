#pragma once

#include <vector>

class Window;

class DesktopSystem
{
    friend class App;

public:
    DesktopSystem();
    ~DesktopSystem();

    Window* create_window(int width, int height);

    std::vector<Window*> windows;
};