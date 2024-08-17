#include "app.h"

#include "SDL.h"
#include "desktop_system.h"
#include "scene.h"
#include "desktop_window.h"

#include "gui.h"
#include "scene_view.h"
#include "console_view.h"

int main(int argc, char* argv[])
{
    App& app = App::get_instance();

    Scene& scene = app.scene_manager.create_scene();
    DesktopWindow* window = app.desktop_system.create_window(1024, 800);
    
    window->scene = &scene;

    window->gui->views.push_back(std::make_unique<ConsoleView>("consoleView"));
    window->gui->views.push_back(std::make_unique<SceneView>("sceneView1", scene));
    window->gui->views.push_back(std::make_unique<SceneView>("sceneView2", scene));

    //auto secondWindow = app.desktop_system.create_window(800, 600);
    //secondWindow->scene = &scene;

    app.run_game_loop();

    return 0;
}