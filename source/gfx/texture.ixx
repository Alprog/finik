export module texture;

import core;
import dx;
import descriptor_handle;
import images;
import gpu_resource;
import blob;
import asset;

export class Texture : public GpuResource, public Asset
{
public:
    Texture(int width, int height);
    Texture(Image& image);
    Texture(Blob& blob);
    
    void HotReload(Blob& blob) override;

    void setData(Image& image);

public:
    int Width;
    int Height;

    D3D12_RESOURCE_STATES state;

    DescriptorHandle descriptorHandle;
};
