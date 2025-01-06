export module effect;

import core;
import render_system_fwd;
import pipeline_settings;
import constant_buffer;

export class Effect
{
public:
    void setVertexShader(std::shared_ptr<Shader> shader);
    void setPixelShader(std::shared_ptr<Shader> shader);

    PipelineState* getPipelineState();

private:
    PipelineSettings pipelineSettings;
    PipelineState* pipelineState;
};
