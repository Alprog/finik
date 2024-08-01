#pragma once

#include "desktop_system.h"
#include "input_system.h"
#include "scene_manager.h"
#include "render_system.h"

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
    SceneManager scene_manager;
    RenderSystem render_system;
};