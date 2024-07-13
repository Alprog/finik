#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

static int const NUM_BACK_BUFFER = 3;
static int const NUM_FRAMES_IN_FLIGHT = 3;

class Window;
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
    SwapChain(Window& window);
    ~SwapChain();

    void CreateRenderTarget();
    void CleanupRenderTarget();
    void WaitForLastSubmittedFrame();
    FrameContext* WaitForNextFrameResources();

    void start_frame(ID3D12GraphicsCommandList* command_list);
    void finish_frame(ID3D12GraphicsCommandList* command_list);
    void present();

public:
    Window& window;

    IDXGISwapChain3* pSwapChain;
    HANDLE hSwapChainWaitableObject;
    ID3D12Resource* mainRenderTargetResource[NUM_BACK_BUFFER] = {};
    D3D12_CPU_DESCRIPTOR_HANDLE  mainRenderTargetDescriptor[NUM_BACK_BUFFER] = {};
    ID3D12Fence* fence = nullptr;
    HANDLE fenceEvent = nullptr;
    UINT64 fenceLastSignaledValue = 0;
    bool swapChainOccluded = false;
    FrameContext frameContext[NUM_FRAMES_IN_FLIGHT] = {};
    UINT frameIndex = 0;
    FrameContext* current_frame_ctx;
}; 