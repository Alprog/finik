export module tile_map;

import std;
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