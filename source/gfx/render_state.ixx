export module render_state;

import core;
import render_system_fwd;
import pipeline_settings;
import constant_buffer;

export class RenderState
{
public:
    RenderState();

    void setVertexShader(Shader* shader);
    void setPixelShader(Shader* shader);

    GpuFrameConstantBuffer* constantBuffer;

    PipelineState* getPipelineState();

private:
    PipelineSettings pipelineSettings;
    PipelineState* pipelineState;
};
