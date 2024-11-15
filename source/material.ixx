export module material;

import core;
import texture;
import texture_id;

export struct MaterialData
{
    Color ColorA;
    Color ColorB;
    Color ColorC;
    Color ColorD;
    int32 TextureA;
    int32 TextureB;
    int32 TextureC;
    int32 TextureD;
};

export struct MaterialsConstantBuffer
{
    MaterialData Materials[80];
};

export class Material
{
public:
    Material(std::string name);
    ~Material();

    void RefreshBuffer();

    std::string Name;
    std::vector<Color> Colors;
    std::vector<Texture*> Textures;

    int32 Index;
};

static_assert(sizeof(MaterialData) == 80);