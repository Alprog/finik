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
