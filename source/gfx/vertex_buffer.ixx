export module vertex_buffer;

import std;
import dx;
import vertex;

export class VertexBuffer
{
public:
    void Load();
    
    std::vector<StandardVertex> vertices;
    MyPtr<ID3D12Resource> vertexBufferResource;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};
