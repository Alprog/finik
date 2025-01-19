export module render_surface;

import core;
import descriptor_handle;
import dx;
import command_list;

export class RenderSurface
{
public:
    void init(IntSize resolution);
    void createHandles();

    void resize(IntSize resolution);
    void recreateRenderTarget();
    void recreateDepthStencil();

    void startRendering(CommandList& commandList);
    void endRendering(CommandList& commandList);

    IntSize resolution;

    MyPtr<ID3D12Resource> renderTarget;
    DescriptorHandle renderTargetHandle;
    DescriptorHandle textureHandle;

    MyPtr<ID3D12Resource> depthStencil;
    DescriptorHandle depthStencilHandle;

    D3D12_VIEWPORT viewport = {0};
    D3D12_RECT scissorRect;
};