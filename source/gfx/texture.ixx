module;
#include "dx.h"
class Image;
export module texture;

import dx;
import std;
import descriptor_handle;

export class Texture
{
public:
    Texture(int width, int height);
    Texture(Image& image);
    Texture(std::string filePath);

    void setData(Image& image);

public:
    ComPtr<ID3D12Resource> resource;
    int Width;
    int Height;

    DescriptorHandle descriptorHandle;
};