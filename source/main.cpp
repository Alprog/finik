#include "app.h"

#include "SDL.h"
#include "desktop_system.h"
#include "scene.h"
#include "desktop_window.h"

#include "gui.h"
#include "sceneView.h"
#include "consoleView.h"

int main(int argc, char* argv[])
{
    App& app = App::get_instance();

    Scene& scene = app.scene_manager.create_scene();
    DesktopWindow* window = app.desktop_system.create_window(1024, 800);
    
    window->scene = &scene;

    window->gui->views.push_back(std::make_unique<ConsoleView>("consoleView"));
    window->gui->views.push_back(std::make_unique<SceneView>("sceneView", scene));

    //auto secondWindow = app.desktop_system.create_window(800, 600);
    //secondWindow->scene = &scene;

    app.run_game_loop();

    return 0;
}