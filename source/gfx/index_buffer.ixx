module;
#include "dx.h"
export module index_buffer;

import dx;
import std;

export class IndexBuffer
{
public:
    void Load();

    std::vector<unsigned int> indices;
    ComPtr<ID3D12Resource> indexBufferResource;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
