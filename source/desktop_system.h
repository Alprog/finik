#pragma once

#include <cstdint>
import std;

class DesktopWindow;

class DesktopSystem
{
    friend class App;

public:
    DesktopSystem();
    ~DesktopSystem();

    DesktopWindow* create_window(int width, int height);
    DesktopWindow* get_window_by_id(uint32_t id) const;
    void close_window(DesktopWindow* window);

    std::vector<DesktopWindow*> windows;
};