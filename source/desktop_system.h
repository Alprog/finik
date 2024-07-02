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
    Window* get_window_by_id(uint32_t id) const;
    void close_window(Window* window);

    std::vector<Window*> windows;
};