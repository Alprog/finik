module grid;

import mesh_builder;
import images;

Grid::Grid()
{
    tileMap = new ::TileMap();
	mesh = CreateMesh();

	auto cellTexture = new Texture("C:/finik/textures/cell.png");

	material = new Material("grid_material");
	material->Textures.push_back(cellTexture);
	material->Textures.push_back(tileMap->Texture);
	material->RefreshBuffer();
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