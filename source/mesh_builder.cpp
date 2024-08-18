#include "mesh_builder.h"

void MeshBuilder::AddTile(int x, int y)
{
    auto vertexCount = Vertices.size();

    Vertices.push_back({ Vector3(x + 0, y + 0, 0), Vector3(0, 0, 1), Vector2(0, 0), x, y });
    Vertices.push_back({ Vector3(x + 1, y + 0, 0), Vector3(0, 0, 1), Vector2(1, 0), x, y });
    Vertices.push_back({ Vector3(x + 0, y + 1, 0), Vector3(0, 0, 1), Vector2(1, 0), x, y });
    Vertices.push_back({ Vector3(x + 1, y + 1, 0), Vector3(0, 0, 1), Vector2(1, 1), x, y });
    
    int i = vertexCount;
    Indices.push_back(i + 0);
    Indices.push_back(i + 1);
    Indices.push_back(i + 2);

    Indices.push_back(i + 2);
    Indices.push_back(i + 1);
    Indices.push_back(i + 3);
}