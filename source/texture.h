#pragma once

#include "dx.h"
#include <vector>

#include "descriptor_handle.h"

class Texture
{
public:
    Texture(std::string filePath);

public:
    ComPtr<ID3D12Resource> texture;
    int width;
    int height;

    DescriptorHandle descriptorHandle;
};
