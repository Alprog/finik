#pragma once

#include "desktop_system.h"
#include "input_system.h"
#include "render_system.h"
#include "gui_system.h"

class Window;

class App
{
public:
    static App& get_instance();

private:
    App();

public:
    void run_game_loop();

public:
    DesktopSystem desktop_system;
    InputSystem input_system;
    RenderSystem render_system;
    GuiSystem gui_system;
};