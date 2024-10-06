module;
#include <cstdint>
export module mesh_builder;

import std;
import vertex;
import mesh;

export class MeshBuilder
{
public:
    std::vector<StandardVertex> Vertices;
    std::vector<uint32_t> Indices;

    void AddTile(int x, int y);
    Mesh* Build();
};