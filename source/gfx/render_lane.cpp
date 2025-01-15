module;
#include "dx.h"
module render_lane;

import app;
import render_system;
import fence;
import command_queue;
import command_list;
import timebox_tracker;
import descriptor_heap;
import timer;
import log;
import camera;
import scene;

void RenderSurface::init(IntSize resolution)
{
    createHandles();
    resize(resolution);
}

void RenderSurface::createHandles()
{
    RenderSystem& render_system = App::GetInstance().render_system;
    renderTargetHandle = render_system.getRtvHeap()->getNextHandle();
    textureHandle = render_system.getCommonHeap()->getNextHandle();
    depthStencilHandle = render_system.getDsvHeap()->getNextHandle();
}

void RenderSurface::resize(IntSize resolution)
{
    this->resolution = resolution;
    recreateRenderTarget();
    recreateDepthStencil();
}

void RenderSurface::recreateRenderTarget()
{
    RenderSystem& render_system = App::GetInstance().render_system;
    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<uint32>(resolution.width),
        static_cast<uint32>(resolution.height),
        1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    auto result = render_system.get_device()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        &clearValue,
        IID_PPV_ARGS(&renderTarget));
    if (FAILED(result))
        throw;

    render_system.get_device()->CreateRenderTargetView(renderTarget.Get(), nullptr, renderTargetHandle.getCPU());
    render_system.get_device()->CreateShaderResourceView(renderTarget.Get(), nullptr, textureHandle.getCPU());
}

void RenderSurface::recreateDepthStencil()
{
    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<uint32>(resolution.width),
        static_cast<uint32>(resolution.height),
        1, 1, DXGI_FORMAT_D32_FLOAT, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_D32_FLOAT;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    RenderSystem& render_system = App::GetInstance().render_system;

    auto result = render_system.get_device()->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearValue,
        IID_PPV_ARGS(&depthStencil));
    if (FAILED(result))
        throw;

    depthStencil->SetName(L"DepthStencil");

    render_system.get_device()->CreateDepthStencilView(depthStencil.Get(), nullptr, depthStencilHandle.getCPU());
}

void RenderSurface::startRendering(ID3D12GraphicsCommandList* commandList)
{
    RenderSystem& render_system = App::GetInstance().render_system;

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = renderTarget.Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    commandList->ResourceBarrier(1, &barrier);

    // Render Dear ImGui graphics
    const float clear_color_with_alpha[4] = {0.5f, 0.2f, 0.2f, 1.0f};

    commandList->ClearRenderTargetView(renderTargetHandle.getCPU(), clear_color_with_alpha, 0, nullptr);
    commandList->ClearDepthStencilView(depthStencilHandle.getCPU(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    commandList->OMSetRenderTargets(1, &renderTargetHandle.getCPU(), FALSE, &depthStencilHandle.getCPU());

    ID3D12DescriptorHeap* a = render_system.getCommonHeap()->get();
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
    : scene{scene}
    , camera{camera}
{
    surface.init(resolution);
}

void RenderLane::resize(IntSize resolution)
{
    if (surface.resolution != resolution)
    {
        RenderSystem& render_system = App::GetInstance().render_system;
        render_system.get_command_queue().Flush();

        surface.resize(resolution);
        camera.AspectRatio = static_cast<float>(resolution.width) / resolution.height;
        camera.calcProjectionMatrix();
    }
}

RenderSurface& RenderLane::getSurface()
{
    return surface;
}

void RenderLane::render()
{
    RenderSystem& render_system = App::GetInstance().render_system;
    auto& commandQueue = render_system.get_command_queue();
    {
        Profile _("wait");
        commandQueue.fence->WaitForValue(fenceValue);
    }

    CommandList& commandList = render_system.getFreeCommandList();
    commandList.startRecording();

    surface.startRendering(commandList.listImpl.Get());

    RenderContext context(render_system, *commandList.listImpl.Get());
    scene.render(context, &camera);
    surface.endRendering(commandList.listImpl.Get());

    commandList.endRecording();
    commandQueue.execute(commandList);

    fenceValue = commandQueue.fence->SignalNext();
}
