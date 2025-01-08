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
    PipelineSettings();

    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> pixelShader;

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
        return lhs.vertexShader == rhs.vertexShader &&
            lhs.pixelShader == rhs.pixelShader;
    }
};

export template <>
struct std::hash<PipelineSettings>
{
    size_t operator()(const PipelineSettings& settings) const
    {
        size_t h1 = std::hash<int32>()(settings.vertexShader->bytecode.id);
        size_t h2 = std::hash<int32>()(settings.pixelShader->bytecode.id);
        return h1 ^ (h2 << 1);
    }
};
