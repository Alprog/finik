module tile_map;

import texture;
import images;

TileMap::TileMap()
{
    Image = new ::Image();
    Image->width = 256;
    Image->height = 256;
    Image->data = new Texel[Image->width * Image->height];
    Image->generateChessboard();

    Texture = std::make_shared<::Texture>(*Image);
}