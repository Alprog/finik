#pragma once

#include "gfx/dx.h"
#include "path.h"

class DXRenderer;

enum ShaderType
{
    Vertex,
    Pixel
};

class Shader
{
public:
    Shader(Path path, ShaderType type, const std::string& entryPoint);

    ShaderType type;
    ComPtr<ID3DBlob> blob;
};
