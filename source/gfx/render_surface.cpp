module;
#include "dx.h"
module render_surface;

import render_system;

void RenderSurface::init(IntSize resolution)
{
    createHandles();
    resize(resolution);
}

void RenderSurface::createHandles()
{
    RenderSystem& render_system = Single::Get<RenderSystem>();
    renderTargetHandle = render_system.getRtvHeap()->getNextHandle();
    textureHandle = render_system.getCommonHeap()->getNextHandle();
    depthStencilHandle = render_system.getDsvHeap()->getNextHandle();
    depthTextureHandle = render_system.getCommonHeap()->getNextHandle();
}

void RenderSurface::resize(IntSize resolution)
{
    this->resolution = resolution;
    recreateRenderTarget();
    recreateDepthStencil();
}

void RenderSurface::recreateRenderTarget()
{
    RenderSystem& render_system = Single::Get<RenderSystem>();
    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<uint32>(resolution.width),
        static_cast<uint32>(resolution.height),
        1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    renderTarget.reinit(resourceDesc, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, &clearValue);

    render_system.get_device()->CreateRenderTargetView(renderTarget.getInternal(), nullptr, renderTargetHandle.getCPU());
    render_system.get_device()->CreateShaderResourceView(renderTarget.getInternal(), nullptr, textureHandle.getCPU());
}

void RenderSurface::recreateDepthStencil()
{
    CD3DX12_RESOURCE_DESC resourceDesc(
        D3D12_RESOURCE_DIMENSION_TEXTURE2D, 0,
        static_cast<uint32>(resolution.width),
        static_cast<uint32>(resolution.height),
        1, 1, DXGI_FORMAT_D32_FLOAT, 1, 0,
        D3D12_TEXTURE_LAYOUT_UNKNOWN,
        D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

    D3D12_CLEAR_VALUE clearValue;
    clearValue.Format = DXGI_FORMAT_D32_FLOAT;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    RenderSystem& render_system = Single::Get<RenderSystem>();

    depthStencil.reinit(resourceDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clearValue);

    render_system.get_device()->CreateDepthStencilView(depthStencil.getInternal(), nullptr, depthStencilHandle.getCPU());

    // Create the shader resource view
    D3D12_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
    SRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
    SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    SRVDesc.Texture2D.MipLevels = 1;

    SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    render_system.get_device()->CreateShaderResourceView(depthStencil.getInternal(), &SRVDesc, depthTextureHandle.getCPU());
}

void RenderSurface::startRendering(CommandList& commandList)
{
    RenderSystem& render_system = Single::Get<RenderSystem>();

    commandList.transition(renderTarget, D3D12_RESOURCE_STATE_RENDER_TARGET);
    commandList.transition(depthStencil, D3D12_RESOURCE_STATE_DEPTH_WRITE);

    const float clear_color_with_alpha[4] = {0.5f, 0.2f, 0.2f, 1.0f};
    commandList.listImpl->ClearRenderTargetView(renderTargetHandle.getCPU(), clear_color_with_alpha, 0, nullptr);
    commandList.listImpl->ClearDepthStencilView(depthStencilHandle.getCPU(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    commandList.listImpl->OMSetRenderTargets(1, &renderTargetHandle.getCPU(), FALSE, &depthStencilHandle.getCPU());

    ID3D12DescriptorHeap* a = render_system.getCommonHeap()->get();
    commandList.listImpl->SetDescriptorHeaps(1, &a);

    viewport.Width = static_cast<float>(resolution.width);
    viewport.Height = static_cast<float>(resolution.height);
    viewport.MaxDepth = 1.0f;
    commandList.listImpl->RSSetViewports(1, &viewport);

    scissorRect.right = static_cast<LONG>(resolution.width);
    scissorRect.bottom = static_cast<LONG>(resolution.height);
    commandList.listImpl->RSSetScissorRects(1, &scissorRect);
}

void RenderSurface::endRendering(CommandList& commandList)
{
    commandList.transition(renderTarget, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    commandList.transition(depthStencil, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}