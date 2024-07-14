#include "swap_chain.h"

#include "window.h"

#include "app.h"

#include <dxgi.h>

D3D12_VIEWPORT viewport;
D3D12_RECT scissorRect;

SwapChain::SwapChain(Window& window)
    : window{ window }
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC1 sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = NUM_BACK_BUFFER;
        sd.Width = 0;
        sd.Height = 0;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.Stereo = FALSE;
    }

    RenderSystem& render_system = App::get_instance().render_system;

    {
        ComPtr<IDXGIFactory3> dxgiFactory;
        ComPtr<IDXGISwapChain1> dxgiSwapChain1;
      
        UINT createFactoryFlags = 0;
#if defined(_DEBUG)
        createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif
        auto result = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory));
        if (FAILED(result)) throw;

        result = dxgiFactory->CreateSwapChainForHwnd(render_system.get_command_queue(), window.hwnd, &sd, nullptr, nullptr, &dxgiSwapChain1);
        if (FAILED(result)) throw;

        result = dxgiSwapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
        if (FAILED(result)) throw;

        swapChain->SetMaximumFrameLatency(NUM_BACK_BUFFER);
        hSwapChainWaitableObject = swapChain->GetFrameLatencyWaitableObject();
    }

    CreateRenderTargets();
    CreateDepthStencil();

    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (render_system.get_device()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&frameContext[i].CommandAllocator)) != S_OK)
            throw;

    if (render_system.get_device()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)) != S_OK)
        throw;

    fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (fenceEvent == nullptr)
        throw;
}

SwapChain::~SwapChain()
{
    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (frameContext[i].CommandAllocator) { frameContext[i].CommandAllocator->Release(); frameContext[i].CommandAllocator = nullptr; }

    if (swapChain) { swapChain->SetFullscreenState(false, nullptr); }
    if (hSwapChainWaitableObject != nullptr) { CloseHandle(hSwapChainWaitableObject); }
    if (fence) { fence->Release(); fence = nullptr; }
    if (fenceEvent) { CloseHandle(fenceEvent); fenceEvent = nullptr; }
}

void SwapChain::CreateRenderTargets()
{
    RenderSystem& render_system = App::get_instance().render_system;

    for (UINT i = 0; i < NUM_BACK_BUFFER; i++)
    {
        auto renderTarget = std::make_shared<RenderTarget>();
        
        renderTarget->handle = render_system.getRtvHeap()->getNextHandle().getCPU();

        ID3D12Resource* pBackBuffer = nullptr;
        swapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
        render_system.get_device()->CreateRenderTargetView(pBackBuffer, nullptr, renderTarget->handle);
        renderTarget->resource = pBackBuffer;
    
        renderTargets.push_back(renderTarget);
    }
}

void SwapChain::CreateDepthStencil()
{
    /*CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<UINT>(width),
        static_cast<UINT>(height),
        1, 1, DXGI_FORMAT_D32_FLOAT, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_D32_FLOAT;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    RenderSystem& render_system = App::get_instance().render_system;

    result = render_system.get_device()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearValue,
        IID_PPV_ARGS(&depthStencil));
    if (FAILED(result)) throw;

    depthStencil->SetName(L"DepthStencil");

    device->CreateDepthStencilView(depthStencil.Get(), nullptr, dsvHeap->GetCPUDescriptorHandleForHeapStart());*/
}

void SwapChain::CleanupRenderTarget()
{
    WaitForLastSubmittedFrame();
}

void SwapChain::WaitForLastSubmittedFrame()
{
    FrameContext* frameCtx = &frameContext[frameIndex % NUM_FRAMES_IN_FLIGHT];

    UINT64 fenceValue = frameCtx->FenceValue;
    if (fenceValue == 0)
        return; // No fence was signaled

    frameCtx->FenceValue = 0;
    if (fence->GetCompletedValue() >= fenceValue)
        return;

    fence->SetEventOnCompletion(fenceValue, fenceEvent);
    WaitForSingleObject(fenceEvent, INFINITE);
}

FrameContext* SwapChain::WaitForNextFrameResources()
{
    UINT nextFrameIndex = frameIndex + 1;
    frameIndex = nextFrameIndex;

    HANDLE waitableObjects[] = { hSwapChainWaitableObject, nullptr };
    DWORD numWaitableObjects = 1;

    FrameContext* frameCtx = &frameContext[nextFrameIndex % NUM_FRAMES_IN_FLIGHT];
    UINT64 fenceValue = frameCtx->FenceValue;
    if (fenceValue != 0) // means no fence was signaled
    {
        frameCtx->FenceValue = 0;
        fence->SetEventOnCompletion(fenceValue, fenceEvent);
        waitableObjects[1] = fenceEvent;
        numWaitableObjects = 2;
    }

    WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

    return frameCtx;
}

void SwapChain::start_frame(ID3D12GraphicsCommandList* command_list)
{
    RenderSystem& render_system = App::get_instance().render_system;

    current_frame_ctx = WaitForNextFrameResources();
    UINT backBufferIdx = swapChain->GetCurrentBackBufferIndex();
    current_frame_ctx->CommandAllocator->Reset();

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = renderTargets[backBufferIdx]->resource.Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    command_list->Reset(current_frame_ctx->CommandAllocator, nullptr);
    command_list->ResourceBarrier(1, &barrier);

    // Render Dear ImGui graphics
    const float clear_color_with_alpha[4] = { 0.5f, 0.0f, 0.5f, 1.0f };

    auto handle = renderTargets[backBufferIdx]->handle;
    command_list->ClearRenderTargetView(handle, clear_color_with_alpha, 0, nullptr);
    command_list->OMSetRenderTargets(1, &handle, FALSE, nullptr);
    
    ID3D12DescriptorHeap* a = render_system.getSrvCbvHeap()->get();
    command_list->SetDescriptorHeaps(1, &a);

    viewport.Width = static_cast<float>(1024);
    viewport.Height = static_cast<float>(800);
    viewport.MaxDepth = 1.0f;
    command_list->RSSetViewports(1, &viewport);

    scissorRect.right = static_cast<LONG>(1024);
    scissorRect.bottom = static_cast<LONG>(800);
    command_list->RSSetScissorRects(1, &scissorRect);
}

void SwapChain::finish_frame(ID3D12GraphicsCommandList* command_list)
{
    UINT backBufferIdx = swapChain->GetCurrentBackBufferIndex();

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = renderTargets[backBufferIdx]->resource.Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    command_list->ResourceBarrier(1, &barrier);
    command_list->Close();

    RenderSystem& render_system = App::get_instance().render_system;
    render_system.get_command_queue()->ExecuteCommandLists(1, (ID3D12CommandList* const*)&command_list);
}

void SwapChain::present()
{
    RenderSystem& render_system = App::get_instance().render_system;

    // Present
    HRESULT hr = swapChain->Present(1, 0);   // Present with vsync
    //HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
    swapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);

    UINT64 fenceValue = fenceLastSignaledValue + 1;
    render_system.get_command_queue()->Signal(fence, fenceValue);
    fenceLastSignaledValue = fenceValue;
    current_frame_ctx->FenceValue = fenceValue;
}