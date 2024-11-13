export module tile_map;

import core;
import texture;
import images;

export class TileMap
{
public:
    TileMap();

    Image* Image;
    Texture* Texture;
    bool Changed;
};