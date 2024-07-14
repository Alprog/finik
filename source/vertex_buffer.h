#pragma once

#include "dx.h"

#include "vertex.h"

class VertexBuffer
{
public:
    void Load();
    
    std::vector<StandardVertex> vertices;
    ComPtr<ID3D12Resource> vertexBufferResource;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};