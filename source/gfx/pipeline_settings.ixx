export module pipeline_settings;

import core;
import render_system_fwd;
import shader;

export enum class CullMode : char
{
    None,
    Front,
    Back
};

export class PipelineSettings
{
public:
    PipelineSettings() = default;
    PipelineSettings(ShaderByteCode vertexByteCode, ShaderByteCode pixelByteCode);

    ShaderByteCode vertexByteCode;
    ShaderByteCode pixelByteCode;

    union
    {
        struct
        {
            CullMode cullMode : 2;
        };
        unsigned int flags;
    };

    inline friend bool operator ==(const PipelineSettings& lhs, const PipelineSettings& rhs)
    {
        return lhs.vertexByteCode == rhs.vertexByteCode &&
            lhs.pixelByteCode == rhs.pixelByteCode;
    }
};

export template <>
struct std::hash<PipelineSettings>
{
    size_t operator()(const PipelineSettings& settings) const
    {
        size_t h1 = std::hash<void*>()(settings.vertexByteCode.Get());
        size_t h2 = std::hash<void*>()(settings.pixelByteCode.Get());
        return h1 ^ (h2 << 1);
    }
};
