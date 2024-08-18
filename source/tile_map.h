#pragma once

#include <vector>

class Image;
class Texture;

class TileMap
{
public:
    TileMap();

    Image* Image;
    Texture* Texture;
    bool Changed;
};