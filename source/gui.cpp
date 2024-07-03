#include "gui.h"

#include "imgui.h"
#include "backends/imgui_impl_dx12.h"
#include "backends/imgui_impl_sdl2.h"

#include "window.h"
#include "app.h"

Gui::Gui(Window& window)
    : window{window}
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    impl = ImGui::CreateContext();
    ImGui::SetCurrentContext(impl);


    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();


    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForD3D(window.get_impl());

    RenderSystem& render_system = App::get_instance().render_system;
    render_system.ImguiInitHelper();
}

Gui::~Gui()
{
    ImGui::SetCurrentContext(impl);
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::set_context()
{
    ImGui::SetCurrentContext(impl);
}