module;
#include <cstdint>
export module mesh;

import vertex;
import vertex_buffer;
import index_buffer;
import std;

export class Mesh
{
public:
    std::vector<StandardVertex> vertices;
    std::vector<uint32_t> indices;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

export Mesh* createCubeMesh();
