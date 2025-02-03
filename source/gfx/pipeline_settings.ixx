export module pipeline_settings;

import core;
import render_system_fwd;
import shader;

export enum class PipelineType : char
{
    Standard,
    Imgui
};

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

    PipelineType type = PipelineType::Standard;

    ShaderByteCode vertexByteCode;
    ShaderByteCode pixelByteCode;

    CullMode cullMode;

    inline friend bool operator==(const PipelineSettings& lhs, const PipelineSettings& rhs) = default;
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
