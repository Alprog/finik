export module mesh;

import types;
import vertex;
import vertex_buffer;
import index_buffer;
import std;

export class Mesh
{
public:
    std::vector<StandardVertex> vertices;
    std::vector<uint32> indices;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

export Mesh* createCubeMesh();
