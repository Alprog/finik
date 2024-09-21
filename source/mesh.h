#pragma once

#include "gfx/vertex_buffer.h"

import std.compat;

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
