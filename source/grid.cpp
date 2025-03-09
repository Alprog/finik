module grid;

import mesh_builder;
import images;
import assets;
import effect_manager;

Grid::Grid()
{
    tileMap = new ::TileMap();
	mesh = CreateMesh();

	auto cellTexture = Assets::GetInstance().get<Texture>("textures/cell.png");

	material = new Material("grid_material");
	material->Textures.append(cellTexture);
	material->Textures.append(tileMap->Texture);
	material->Effect = EffectManager::GetInstance().get("grid");
    material->ShadowEffect = EffectManager::GetInstance().getShadowEffect(*material->Effect);
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