export module texture;

import core;
import dx;
import descriptor_handle;
import images;
import gpu_resource;

export class Texture : public GpuResource
{
public:
    Texture(int width, int height);
    Texture(Image& image);
    Texture(std::string filePath);

    void setData(Image& image);

public:
    int Width;
    int Height;

    DescriptorHandle descriptorHandle;
};
