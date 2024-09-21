#pragma once

#include <vector>
#include "gfx/vertex.h"

class Mesh;

class MeshBuilder
{
public:
    std::vector<StandardVertex> Vertices;
    std::vector<uint32_t> Indices;

    void AddTile(int x, int y);
    Mesh* Build();
};