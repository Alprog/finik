module;
#include "dx.h"
#include <cstdint>
class Scene;
class Camera;
export module render_lane;

import descriptor_handle;
import int_size;

export class RenderSurface
{
public:
    void init(IntSize resolution);
    void createHandles();

    void resize(IntSize resolution);
    void recreateRenderTarget();
    void recreateDepthStencil();

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

export class RenderLane
{
public:
    RenderLane(Scene& scene, Camera& camera, IntSize resolution);
    void resize(IntSize resolution);

    RenderSurface& getSurface();
    void render(); 

private:
    Scene& scene;
    Camera& camera;
    RenderSurface surface;

    uint64_t fenceValue = 0;
};