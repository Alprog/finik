#include "app.h"

#include "SDL.h"
#include "desktop_system.h"

int main(int argc, char* argv[])
{
    App& app = App::get_instance();

    Window* window = app.desktop_system.create_window(1024, 800);
    //app.desktop_system.create_window(800, 600);

    app.run_game_loop();

    return 0;
}