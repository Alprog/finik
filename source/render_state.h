#pragma once

class Shader;
class Texture;
class ConstantBuffer;
class PipelineState;

#include "pipeline_settings.h"

class RenderState
{
public:
    RenderState();

    void setVertexShader(Shader* shader);
    void setPixelShader(Shader* shader);

    Texture* texture;
    ConstantBuffer* constantBuffer;

    PipelineState* getPipelineState();

private:
    PipelineSettings pipelineSettings;
    PipelineState* pipelineState;
};
