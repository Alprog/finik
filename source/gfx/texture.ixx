export module texture;

import core;
import dx;
import descriptor_handle;
import images;

export class Texture
{
public:
    Texture(int width, int height);
    Texture(Image& image);
    Texture(std::string filePath);

    void setData(Image& image);

public:
    MyPtr<ID3D12Resource> resource;
    int Width;
    int Height;

    DescriptorHandle descriptorHandle;
};
