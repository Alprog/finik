#include "grid.h"

#include "mesh_builder.h"
#include "images.h"

Grid::Grid()
{
    tileMap = new ::TileMap();
	mesh = CreateMesh();
}

Mesh* Grid::CreateMesh()
{
	MeshBuilder builder;

	int width = tileMap->Image->width;
	int heigth = tileMap->Image->height;

	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			builder.AddTile(x, y);
		}
	}

	return builder.Build();
}