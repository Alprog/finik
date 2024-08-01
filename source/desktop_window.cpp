#include "desktop_window.h"

#include <SDL.h>
#include <SDL_syswm.h>

#include "gui.h"
#include "swap_chain.h"

#include "app.h"
#include "render_system.h"
#include "scene.h"

DesktopWindow::DesktopWindow(int width, int height)
    : width{width}
    , height{height}
{
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    impl = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    id = SDL_GetWindowID(impl);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(impl, &wmInfo);
    hwnd = (HWND)wmInfo.info.win.window;

    swap_chain = new SwapChain(*this);
    gui = new Gui(*this);
}

DesktopWindow::~DesktopWindow()
{
    delete gui;
    delete swap_chain;
    SDL_DestroyWindow(impl);
}

void DesktopWindow::renderScene()
{
    if (scene != nullptr)
    {
        auto context = App::get_instance().render_system.getRenderContext();
        scene->render(*context);
    }
}