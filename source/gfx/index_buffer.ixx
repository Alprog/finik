export module index_buffer;

import core;
import dx;

export class IndexBuffer
{
public:
    void Load();

    std::vector<unsigned int> indices;
    MyPtr<ID3D12Resource> indexBufferResource;
    D3D12_INDEX_BUFFER_VIEW indexBufferView;
};
