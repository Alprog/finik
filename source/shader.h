#pragma once

#include "gfx/dx.h"

import path;

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
