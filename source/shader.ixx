export module shader;

import core;
import dx;
import asset_path;
import asset_dependencies;

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

    bool isValid() const { return errorMessage.empty(); }

    bool hotRecompile();

    ShaderKey key;
    ShaderByteCode bytecode;
    String errorMessage;
    AssetDependencies hotreloadDependencies;
};
