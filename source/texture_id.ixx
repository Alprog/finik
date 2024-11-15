export module texture_id;

import core;

class Texture;

export struct TextureId
{
    Texture* Get();

    uint32 Index;
};