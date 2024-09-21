#pragma once

#include "gfx/dx.h"
import std;

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