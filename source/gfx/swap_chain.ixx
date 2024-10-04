module;
#include <cstdint>
export module swap_chain;

import dx;
import descriptor_handle;
import render_system_fwd;
import std;
import render_target;

static int const NUM_BACK_BUFFER = 3;
static int const NUM_FRAMES_IN_FLIGHT = 3;

class DesktopWindow;

export struct FrameContext
{
    ID3D12CommandAllocator* CommandAllocator;
    uint64_t                FenceValue;
};

export class SwapChain
{
public:
    SwapChain(DesktopWindow& window);
    ~SwapChain();

    void CreateRenderTarget();
    void CreateRenderTargets();
    void CreateDepthStencil();
    void CleanupRenderTarget();
    void WaitForLastSubmittedFrame();
    FrameContext* WaitForNextFrameResources();

    void start_frame(ID3D12GraphicsCommandList* command_list);
    void finish_frame(ID3D12GraphicsCommandList* command_list);
    void execute(ID3D12GraphicsCommandList* command_list);
    void present();

public:
    DesktopWindow& window;

    ComPtr<IDXGISwapChain3> swapChain;

    HANDLE hSwapChainWaitableObject;
    std::vector<std::shared_ptr<RenderTarget>> renderTargets;
    std::shared_ptr<RenderTarget> renderTarget;

    ComPtr<ID3D12Resource> depthStencil;
    DescriptorHandle depthStencilHandle;

    bool swapChainOccluded = false;
    FrameContext frameContext[NUM_FRAMES_IN_FLIGHT] = {};
    uint32_t frameIndex = 0;
    FrameContext* current_frame_ctx;
}; 