#pragma once

#include <vector>
#include <stdint.h>
#include "gfx/vertex.h"

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
