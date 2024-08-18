#pragma once

#include "dx.h"
#include <vector>
#include "descriptor_handle.h"

class Image;

class Texture
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
