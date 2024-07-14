#pragma once

#include <vector>
#include "vertex.h"
#include <stdint.h>

class VertexBuffer;
class IndexBuffer;

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

Mesh* createCubeMesh();
