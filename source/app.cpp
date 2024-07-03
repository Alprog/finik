#include "app.h"

#include "window.h"

App& App::get_instance()
{
    static App theApp;
    return theApp;
}

App::App()
    : desktop_system{}
    , input_system{}
    , render_system{}
    , gui_system{}
{
}

void App::run_game_loop()
{

}