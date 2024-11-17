export module images;

import core;
import texel;
import blob;

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
    Image* loadPng(Blob& blob);
}
