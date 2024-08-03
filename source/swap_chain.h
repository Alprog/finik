#pragma once

#include "dx.h"

#include "render_target.h"

static int const NUM_BACK_BUFFER = 3;
static int const NUM_FRAMES_IN_FLIGHT = 3;

class DesktopWindow;
class ID3D12Fence;
class IDXGISwapChain3;
class FrameContext;
struct ID3D12GraphicsCommandList;

struct FrameContext
{
    ID3D12CommandAllocator* CommandAllocator;
    UINT64                  FenceValue;
};

typedef void* HANDLE;

class SwapChain
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
    void present();

public:
    DesktopWindow& window;

    ComPtr<IDXGISwapChain3> swapChain;

    HANDLE hSwapChainWaitableObject;
    std::vector<std::shared_ptr<RenderTarget>> renderTargets;
    std::shared_ptr<RenderTarget> renderTarget;

    ComPtr<ID3D12Resource> depthStencil;
    DescriptorHandle depthStencilHandle;

    ID3D12Fence* fence = nullptr;
    HANDLE fenceEvent = nullptr;
    UINT64 fenceLastSignaledValue = 0;
    bool swapChainOccluded = false;
    FrameContext frameContext[NUM_FRAMES_IN_FLIGHT] = {};
    UINT frameIndex = 0;
    FrameContext* current_frame_ctx;
}; 