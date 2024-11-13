export module mesh;

import core;
import vertex;
import vertex_buffer;
import index_buffer;

export class Mesh
{
public:
    std::vector<StandardVertex> vertices;
    std::vector<uint32> indices;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

export Mesh* createCubeMesh();
