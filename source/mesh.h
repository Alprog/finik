#pragma once

#include <vector>
#include <stdint.h>
#include "vertex.h"

class VertexBuffer;
class IndexBuffer;

struct Mesh
{
    std::vector<StandardVertex> vertices;
    std::vector<uint32_t> indices;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

Mesh* createCubeMesh();
