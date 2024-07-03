#pragma once

class Window;
struct FrameContext;

class RenderSystem
{
public:
    friend class App;

    RenderSystem();

    bool create_swap_chain_and_render_target(Window* window);

    bool CreateDeviceD3D();
    void CleanupDeviceD3D();
    void CreateRenderTarget();
    void CleanupRenderTarget();
    void WaitForLastSubmittedFrame();
    FrameContext* RenderSystem::WaitForNextFrameResources();

    void ImguiInitHelper();

    void finish_frame();
};