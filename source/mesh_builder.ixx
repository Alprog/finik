export module mesh_builder;

import types;
import std;
import vertex;
import mesh;

export class MeshBuilder
{
public:
    std::vector<StandardVertex> Vertices;
    std::vector<uint32> Indices;

    void AddTile(int x, int y);
    Mesh* Build();
};