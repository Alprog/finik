#pragma once

#include <vector>

class TileMap
{


    std::vector<int> Data;
    bool Changed;

    void SetTileIndex(int x, int y, int index);
};