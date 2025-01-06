export module effect;

import core;
import render_system_fwd;
import pipeline_settings;
import constant_buffer;

export class Effect
{
public:
    void setVertexShader(Shader* shader);
    void setPixelShader(Shader* shader);

    PipelineState* getPipelineState();

private:
    PipelineSettings pipelineSettings;
    PipelineState* pipelineState;
};
