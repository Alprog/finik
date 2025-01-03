module mesh_builder;

import mesh;
import vertex_buffer;
import index_buffer;

void MeshBuilder::AddTile(int x, int y)
{
    auto vertexCount = Vertices.count();

    Vertices.append({ Vector3(x + 0, y + 0, 0), Vector3(0, 0, 1), Vector2(0, 0), x, y });
    Vertices.append({ Vector3(x + 1, y + 0, 0), Vector3(0, 0, 1), Vector2(1, 0), x, y });
    Vertices.append({ Vector3(x + 0, y + 1, 0), Vector3(0, 0, 1), Vector2(0, 1), x, y });
    Vertices.append({ Vector3(x + 1, y + 1, 0), Vector3(0, 0, 1), Vector2(1, 1), x, y });
    
    int i = vertexCount;
    Indices.append(i + 0);
    Indices.append(i + 1);
    Indices.append(i + 2);

    Indices.append(i + 2);
    Indices.append(i + 1);
    Indices.append(i + 3);
}

Mesh* MeshBuilder::Build()
{
    Mesh* mesh = new Mesh();

    mesh->vertexBuffer = new VertexBuffer();
    mesh->vertexBuffer->vertices = Vertices;
    mesh->vertexBuffer->Load();

    mesh->indexBuffer = new IndexBuffer();
    mesh->indexBuffer->indices = Indices;
    mesh->indexBuffer->Load();

    return mesh;
}