module;
#include <cstdint>
export module mesh;

import vertex;
import vertex_buffer;
import std;

class VertexBuffer;
class IndexBuffer;

class Mesh
{
public:
    std::vector<StandardVertex> vertices;
    std::vector<uint32_t> indices;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

Mesh* createCubeMesh();
