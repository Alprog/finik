#include "app.h"

#include "window.h"

App& App::get_instance()
{
    static App theApp;
    return theApp;
}

App::App()
    : desktop_system{}
    , input_system{}
    , render_system{}
{
}


#include <SDL.h>
#include <SDL_syswm.h>

#include "imgui.h"
#include "backends/imgui_impl_dx12.h"
#include "backends/imgui_impl_sdl2.h"

#include "app.h"
#include "window.h"
#include "gui.h"

#include "render_system.h"
#include "swap_chain.h"

void handle_input()
{
    auto& desktop_system = App::get_instance().desktop_system;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            auto window = desktop_system.get_window_by_id(event.window.windowID);
            if (window)
            {
                desktop_system.close_window(window);
            }
        }

        if (!desktop_system.windows.empty())
        {
            desktop_system.windows[0]->gui->set_context();
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
    }
}

void App::run_game_loop()
{
    Window* window = App::get_instance().desktop_system.windows[0];

    window->gui->set_context();


    RenderSystem& render_system = App::get_instance().render_system;

    // Main loop
    while (true)
    {
        handle_input();

        if (App::get_instance().desktop_system.windows.empty())
        {
            break;
        }

        // Handle window screen locked
        //if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        //{
        //    ::Sleep(10);
        //    continue;
        //}
        //g_SwapChainOccluded = false;

        auto window = desktop_system.windows[0];

        window->renderScene();

        window->gui->prepare();

        auto command_list = render_system.get_command_list();
        window->swap_chain->start_frame(command_list);
        window->gui->render(command_list);
        window->swap_chain->finish_frame(command_list);

        window->swap_chain->present();
    }

    //render_system.WaitForLastSubmittedFrame();
}