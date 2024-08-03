#include "render_lane.h"

#include "app.h"
#include "render_system.h"
#include "scene.h"

void RenderSurface::init(IntSize resolution)
{
    this->resolution = resolution;
    createRenderTarget();
    createDepthStencil();
}

void RenderSurface::createRenderTarget()
{
    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<UINT>(resolution.width),
        static_cast<UINT>(resolution.height),
        1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

    RenderSystem& render_system = App::get_instance().render_system;

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    auto result = render_system.get_device()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        &clearValue,
        IID_PPV_ARGS(&renderTarget));
    if (FAILED(result)) throw;

    renderTargetHandle = render_system.getRtvHeap()->getNextHandle();
    render_system.get_device()->CreateRenderTargetView(renderTarget.Get(), nullptr, renderTargetHandle.getCPU());

    textureHandle = render_system.getSrvCbvHeap()->getNextHandle();
    render_system.get_device()->CreateShaderResourceView(renderTarget.Get(), nullptr, textureHandle.getCPU());
}

void RenderSurface::createDepthStencil()
{
    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<UINT>(resolution.width),
        static_cast<UINT>(resolution.height),
        1, 1, DXGI_FORMAT_D32_FLOAT, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_D32_FLOAT;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    RenderSystem& render_system = App::get_instance().render_system;

    auto result = render_system.get_device()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearValue,
        IID_PPV_ARGS(&depthStencil));
    if (FAILED(result)) throw;

    depthStencil->SetName(L"DepthStencil");

    auto device = render_system.get_device();
    depthStencilHandle = render_system.getDsvHeap()->getNextHandle();
    device->CreateDepthStencilView(depthStencil.Get(), nullptr, depthStencilHandle.getCPU());
}

void RenderSurface::startRendering(ID3D12GraphicsCommandList* commandList)
{
    RenderSystem& render_system = App::get_instance().render_system;

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = renderTarget.Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    commandList->ResourceBarrier(1, &barrier);

    // Render Dear ImGui graphics
    const float clear_color_with_alpha[4] = { 0.5f, 0.2f, 0.2f, 1.0f };

    commandList->ClearRenderTargetView(renderTargetHandle.getCPU(), clear_color_with_alpha, 0, nullptr);
    commandList->ClearDepthStencilView(depthStencilHandle.getCPU(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    commandList->OMSetRenderTargets(1, &renderTargetHandle.getCPU(), FALSE, &depthStencilHandle.getCPU());

    ID3D12DescriptorHeap* a = render_system.getSrvCbvHeap()->get();
    commandList->SetDescriptorHeaps(1, &a);

    viewport.Width = static_cast<float>(resolution.width);
    viewport.Height = static_cast<float>(resolution.height);
    viewport.MaxDepth = 1.0f;
    commandList->RSSetViewports(1, &viewport);

    scissorRect.right = static_cast<LONG>(resolution.width);
    scissorRect.bottom = static_cast<LONG>(resolution.height);
    commandList->RSSetScissorRects(1, &scissorRect);
}

void RenderSurface::endRendering(ID3D12GraphicsCommandList* commandList)
{
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = renderTarget.Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    commandList->ResourceBarrier(1, &barrier);
}

//--------------------------------------

RenderLane::RenderLane(Scene& scene, Camera& camera, IntSize resolution)
    : scene{ scene }
    , camera{ camera }
{
    RenderSystem& render_system = App::get_instance().render_system;
    auto device = render_system.get_device();

    auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(result)) throw;

    result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList));
    if (FAILED(result)) throw;

    result = commandList->Close();
    if (FAILED(result)) throw;

    result = render_system.get_device()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    if (FAILED(result)) throw;

    fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!fenceEvent) throw;

    surface.init(resolution);
}

RenderSurface& RenderLane::getSurface()
{
    return surface;
}

void RenderLane::render()
{
    if (fenceValue != 0)
    {
        fence->SetEventOnCompletion(fenceValue, fenceEvent);
        WaitForSingleObject(fenceEvent, INFINITE);
    }

    commandAllocator->Reset();
    commandList->Reset(commandAllocator, nullptr);
    
    surface.startRendering(commandList);
    RenderSystem& render_system = App::get_instance().render_system;
    RenderContext context(render_system, *commandList);
    scene.render(context);
    surface.endRendering(commandList);

    commandList->Close();

    render_system.get_command_queue()->ExecuteCommandLists(1, (ID3D12CommandList* const*)&commandList);

    render_system.get_command_queue()->Signal(fence, ++fenceValue);
}
