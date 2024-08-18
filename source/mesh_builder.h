#pragma once

#include <vector>
#include "vertex.h"

class MeshBuilder
{
    std::vector<StandardVertex> Vertices;
    std::vector<uint32_t> Indices;

    void AddTile(int x, int y);
};