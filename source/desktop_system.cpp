#include "desktop_system.h"

#include <SDL.h>
#include "window.h"

DesktopSystem::DesktopSystem()
{
    SDL_Init(SDL_INIT_VIDEO);
}

DesktopSystem::~DesktopSystem()
{
    for (auto& window : windows)
    {
        delete window;
    }
    windows.clear();
}

Window* DesktopSystem::create_window(int width, int height)
{
    auto window = new Window(width, height);
    windows.push_back(window);
    return window;
}

Window* DesktopSystem::get_window_by_id(uint32_t id) const
{
    for (auto& window : windows)
    {
        if (window->id == id)
            return window;
    }
    return nullptr;
}

void DesktopSystem::close_window(Window* window)
{
    auto it = std::find(std::begin(windows), std::end(windows), window);
    if (it != std::end(windows))
    {
        windows.erase(it);
    }
    delete window;
}