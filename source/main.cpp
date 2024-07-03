#include "app.h"

#include "SDL.h"
#include "desktop_system.h"

int demo_main();

int main(int argc, char* argv[])
{
    App& app = App::get_instance();

    Window* window = app.desktop_system.create_window(1024, 800);
    app.desktop_system.create_window(800, 600);
    app.render_system.create_swap_chain_and_render_target(app.desktop_system.windows[0]);

    app.run_game_loop();

    demo_main();

    return 0;
}