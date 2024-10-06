module;
#include "gfx/dx.h"
export module shader;

import path;

export enum ShaderType
{
    Vertex,
    Pixel
};

export class Shader
{
public:
    Shader(Path path, ShaderType type, const std::string& entryPoint);

    ShaderType type;
    ComPtr<ID3DBlob> blob;
};
