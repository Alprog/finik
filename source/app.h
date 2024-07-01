#pragma once

#include "desktop_system.h"
#include "input_system.h"
#include "render_system.h"

class Window;

class App
{
public:
    static App& get_instance();

private:
    App();

public:
    Window* add_window();
    void run_game_loop();

private:
    DesktopSystem DesktopSystem;
    InputSystem InputSystem;
    RenderSystem RenderSystem;
};