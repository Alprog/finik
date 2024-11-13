export module mesh_builder;

import core;
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