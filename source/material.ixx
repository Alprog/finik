export module material;

import core;
import texture;
import texture_id;

export class MaterialData
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

export class Material
{
    Material();
    ~Material();

    std::vector<Color> Colors;
    std::vector<Texture> Textures;

    int32 Index;
};

static_assert(sizeof(MaterialData) == 80);