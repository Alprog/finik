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

    std::shared_ptr<Shader> getVertexShader() { return vertexShader; }
    std::shared_ptr<Shader> getPixelShader() { return pixelShader; }

    void resetPso()
    {
        pipelineState = nullptr;
    }

    PipelineState* getPipelineState();

private:
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> pixelShader;

    PipelineState* pipelineState;
};
