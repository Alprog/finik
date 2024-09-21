#include "tile_map.h"

#include "images.h"
#include "gfx/texture.h"

TileMap::TileMap()
{
    Image = new ::Image();
    Image->width = 256;
    Image->height = 256;
    Image->data = new Texel[Image->width * Image->height];
    Image->generateChessboard();

    Texture = new ::Texture(*Image);
}