#include "app.h"

#include "desktop_window.h"

App& App::get_instance()
{
    static App theApp;
    return theApp;
}

App::App()
    : desktop_system{}
    , input_system{}
    , scene_manager{}
    , render_system{}
    , profiler{}
{
}


#include <SDL.h>
#include <SDL_syswm.h>

#include "app.h"
#include "desktop_window.h"
#include "scene.h"
#include "gui.h"

#include "render_system.h"
#include "swap_chain.h"
#include "render_lane.h"
#include "log.h"
#include "timer.h"
#include "profiler/profiler.h"
#include "profiler/timebox_tracker.h"
#include "gpu_profiler.h"

#include <cassert>

import imgui;

void handle_input()
{
    auto& desktop_system = App::get_instance().desktop_system;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        auto window = desktop_system.get_window_by_id(event.window.windowID);
        if (window)
        {
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                desktop_system.close_window(window);
            }
            else
            {
                window->gui->set_context();
               
            }
        }

        ImGui_ImplSDL2_ProcessEvent(&event);
    }
}

void App::run_game_loop()
{
    RenderSystem& render_system = App::get_instance().render_system;

    profiler.start();

    while (true)
    {
        PROFILE("frame");

        float deltaTime = profiler.getDeltaTime();

        auto completedValue = render_system.get_command_queue().fence->GetCompletedValue();
        render_system.get_command_queue().freeCompletedLists();
        render_system.getProfiler()->grabReadyStamps(completedValue);

        {
            PROFILE("input");
            handle_input();
        }

        if (App::get_instance().desktop_system.windows.empty())
        {
            break;
        }

        {
            PROFILE("update");
            scene_manager.update(deltaTime);
            for (auto window : desktop_system.windows)
            {
                window->gui->set_context();
                for (auto& view : window->gui->views)
                {
                    view->update(deltaTime);
                }
            }
        }

        {
            PROFILE("gui prepare");
            for (auto window : desktop_system.windows)
            {
                window->gui->set_context();
                window->gui->prepare();
            }
        }
       

        {
            PROFILE("lanes");
            for (auto& lane : render_system.lanes)
            {
                lane->render();
            }
        }

        {
            PROFILE("render windows");
            for (auto window : desktop_system.windows)
            {
                auto command_list = render_system.get_command_list();
                window->swap_chain->start_frame(command_list);
                window->renderScene();
                window->gui->render(command_list);
                window->swap_chain->finish_frame(command_list);
                window->swap_chain->execute(command_list);
                window->swap_chain->present();
            }
        }

        {
            PROFILE("render platform windows");
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
            }
        }

        render_system.scheduleQueryResolving();

        auto signaled = render_system.get_command_queue().frameFence->SignalNext();
        assert(signaled == profiler.getFrameIndex());

        profiler.endFrame();
    }

    //render_system.WaitForLastSubmittedFrame();
}

int App::getFrameIndex()
{
    return profiler.getFrameIndex();
}