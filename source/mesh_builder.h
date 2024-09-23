#pragma once

#include "gfx/vertex.h"
#include <cstdint>

import std;

class Mesh;

class MeshBuilder
{
public:
    std::vector<StandardVertex> Vertices;
    std::vector<uint32_t> Indices;

    void AddTile(int x, int y);
    Mesh* Build();
};