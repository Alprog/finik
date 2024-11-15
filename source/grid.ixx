export module grid;

import tile_map;
import mesh;
import material;

export class Grid
{
public:
    Grid();

    Mesh* Grid::CreateMesh();

    TileMap* tileMap;
    Mesh* mesh;
    Material* material;
};