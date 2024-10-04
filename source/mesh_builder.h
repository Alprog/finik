#pragma once

#include <cstdint>

import std;
import vertex;

class Mesh;

class MeshBuilder
{
public:
    std::vector<StandardVertex> Vertices;
    std::vector<uint32_t> Indices;

    void AddTile(int x, int y);
    Mesh* Build();
};