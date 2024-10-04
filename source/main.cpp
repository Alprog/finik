#include "SDL.h"
#include "desktop_system.h"
#include "scene.h"
#include "desktop_window.h"

#include "gui.h"
#include "scene_view.h"
#include "console_view.h"
#include "texture_view.h"
#include "stats_view.h"
#include "timer.h"
#include "profiler_view.h"

import app;

int main(int argc, char* argv[])
{
    initTimer();

    App& app = App::get_instance();

    Scene& scene = app.scene_manager.create_scene();
    DesktopWindow* window = app.desktop_system.create_window(1024, 800);
    
    window->scene = &scene;

    window->gui->views.push_back(std::make_unique<ConsoleView>("consoleView"));
    window->gui->views.push_back(std::make_unique<SceneView>("sceneView1", scene));
    //window->gui->views.push_back(std::make_unique<SceneView>("sceneView2", scene));
    window->gui->views.push_back(std::make_unique<TextureView>("textureView", scene));

    SceneView* sceneView = (SceneView*)window->gui->views[1].get();
    window->gui->views.push_back(std::make_unique<StatsView>("statsView", *sceneView));

    window->gui->views.push_back(std::make_unique<ProfilerView>("profilerView"));

    //auto secondWindow = app.desktop_system.create_window(800, 600);
    //secondWindow->scene = &scene;

    app.run_game_loop();

    return 0;
}