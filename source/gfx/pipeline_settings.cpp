module pipeline_settings;

PipelineSettings::PipelineSettings(ShaderByteCode vertexByteCode, ShaderByteCode pixelByteCode)
    : vertexByteCode{ vertexByteCode }
    , pixelByteCode{ pixelByteCode }
{
}