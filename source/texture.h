#pragma once

#include "dx.h"
#include <vector>

#include "descriptor_handle.h"

class Texture
{
public:
    Texture(std::string filePath);

protected:
    std::vector<UINT8> generateChessboard();

public:
    ComPtr<ID3D12Resource> texture;
    DescriptorHandle descriptorHandle;
};
