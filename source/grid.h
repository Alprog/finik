#pragma once

#include "gfx/dx.h"
#include "tile_map.h"

class Mesh;

class Grid
{
public:
    Grid();

    Mesh* Grid::CreateMesh();

    TileMap* tileMap;
    Mesh* mesh;
};