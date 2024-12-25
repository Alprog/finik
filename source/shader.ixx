export module shader;

import core;
import dx;
import asset_path;

export enum ShaderType
{
    Vertex,
    Pixel
};

export struct ShaderKey
{
    AssetPath AssetPath;
    ShaderType Type;
    std::string EntryPoint;

    bool operator==(const ShaderKey& other) const = default;
};

template <>
struct std::hash<ShaderKey>
{
    std::size_t operator()(const ShaderKey& key) const
    {
        return (hash<std::string>()(key.AssetPath.str())
            ^ (hash<int>()(static_cast<int>(key.Type) << 1)) >> 1)
            ^ (hash<std::string>()(key.EntryPoint) << 1);
    }
};

export using ShaderByteCode = MyPtr<ID3DBlob>;

export class Shader
{
public:
    Shader(ShaderKey key);

    void Recompile();

    ShaderKey key;
    ShaderByteCode bytecodeBlob; // compiled code
};
