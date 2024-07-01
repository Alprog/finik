#include "app.h"

#include "window.h"

App& App::get_instance()
{
    static App theApp;
    return theApp;
}

App::App()
    : DesktopSystem{}
    , InputSystem{}
    , RenderSystem{}
{
}

Window* App::add_window()
{
    return new Window();
}

void App::run_game_loop()
{

}