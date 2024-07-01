#include "app.h"

#include "SDL.h"

int demo_main();

int main(int argc, char* argv[])
{
    App& app = App::get_instance();

    Window* window = app.add_window();
    app.run_game_loop();

    demo_main();


    return 0;
}