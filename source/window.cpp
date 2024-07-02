#include "window.h"

#include <SDL.h>
#include <SDL_syswm.h>

Window::Window(int width, int height)
{
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    impl = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(impl, &wmInfo);
    hwnd = (HWND)wmInfo.info.win.window;
}