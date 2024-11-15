export module material;

import core;
import texture;
import texture_id;

export class Material
{
    Color ColorA;
    Color ColorB;
    Color ColorC;
    Color ColorD;
    TextureId TextureA;
    TextureId TextureB;
    TextureId TextureC;
    TextureId TextureD;
};

static_assert(sizeof(Material) == 80);