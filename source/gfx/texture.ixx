export module texture;

import core;
import dx;
import descriptor_handle;
import images;
import gpu_resource;
import blob;
import asset_path;

export class Texture : public GpuResource
{
public:
    Texture(int width, int height);
    Texture(Image& image);
    Texture(AsssetPath path);
    Texture(Blob& blob);
    
    void HotReload(Blob& blob);

    void setData(Image& image);

public:
    int Width;
    int Height;

    DescriptorHandle descriptorHandle;
};
