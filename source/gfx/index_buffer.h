#pragma once

#include "dx.h"

class Renderer;

class IndexBuffer
{
public:
    void Load();

    std::vector<unsigned int> indices;
    ComPtr<ID3D12Resource> indexBufferResource;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
