#pragma once

#include "path.h"
#include "texel.h"

import std;

class Image
{
public:
    int width;
    int height;
    Texel* data;

    Texel& getTexel(int x, int y);

    void generateChessboard();

    size_t getByteSize() { return width * height * 4; };
};

namespace Images
{
    Image* loadPng(Path path);
}
