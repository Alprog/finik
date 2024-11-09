export module render_target;

import dx;

export class RenderTarget
{
public:
    MyPtr<ID3D12Resource> resource;    // render target texture
    D3D12_CPU_DESCRIPTOR_HANDLE handle;
};