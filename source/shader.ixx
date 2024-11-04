export module shader;

import path;
import dx;

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
    MyPtr<ID3DBlob> blob;
};
