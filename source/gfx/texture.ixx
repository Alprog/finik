export module texture;

import core;
import dx;
import descriptor_handle;
import images;
import gpu_resource;
import blob;

export class Texture : public GpuResource
{
public:
    Texture(int width, int height);
    Texture(Image& image);
    Texture(Path path);

    void HotReload(Blob& blob);

    void setData(Image& image);

public:
    int Width;
    int Height;

    DescriptorHandle descriptorHandle;
};
