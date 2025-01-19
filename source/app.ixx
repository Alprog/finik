export module app;

import core;
import render_system;
import profiler;
import scene_manager;
import input_system;
import desktop_system;

export class App
{
public:
    static App& GetInstance();

private:
    App();

public:
    void run_game_loop();
    int getFrameIndex();

private:
    void handle_input();

public:
    DesktopSystem desktop_system;
    InputSystem input_system;
    SceneManager scene_manager;
    RenderSystem render_system;

    finik::profiler::Profiler profiler;
};