#pragma once

#include "dx.h"
#include "descriptor_handle.h"
#include "int_size.h"

class Scene;
class Camera;

class RenderSurface
{
public:
    void init(IntSize resolution);
    void createRenderTarget();
    void createDepthStencil();

    void startRendering(ID3D12GraphicsCommandList* commandList);
    void endRendering(ID3D12GraphicsCommandList* commandList);

    IntSize resolution;

    ComPtr<ID3D12Resource> renderTarget;
    DescriptorHandle renderTargetHandle;
    DescriptorHandle textureHandle;

    ComPtr<ID3D12Resource> depthStencil;
    DescriptorHandle depthStencilHandle;

    D3D12_VIEWPORT viewport = { 0 };
    D3D12_RECT scissorRect;
};

class RenderLane
{
public:
    RenderLane(Scene& scene, Camera& camera, IntSize resolution);
    
    RenderSurface& getSurface();
    void render();
    
private:
    Scene& scene;
    Camera& camera;
    RenderSurface surface;
    ID3D12CommandAllocator* commandAllocator;
    ID3D12GraphicsCommandList* commandList;

    ID3D12Fence* fence = nullptr;
    HANDLE fenceEvent = nullptr;
    UINT64 fenceValue = 0;
};