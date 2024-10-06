export module images;

import std;
import path;
import texel;

export class Image
{
public:
    int width;
    int height;
    Texel* data;

    Texel& getTexel(int x, int y);

    void generateChessboard();

    size_t getByteSize() { return width * height * 4; };
};

export namespace Images
{
    Image* loadPng(Path path);
}
