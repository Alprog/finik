#pragma once

#include "gfx/dx.h"
import std.compat;

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