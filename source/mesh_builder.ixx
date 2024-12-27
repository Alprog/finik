export module mesh_builder;

import core;
import vertex;
import mesh;

export class MeshBuilder
{
public:
    Array<StandardVertex> Vertices;
    Array<uint32> Indices;

    void AddTile(int x, int y);
    Mesh* Build();
};