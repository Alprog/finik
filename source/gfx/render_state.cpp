module effect;

import pipeline_state;
import app;
import shader;

HashMap<PipelineSettings, PipelineState*> states;

void Effect::setVertexShader(Shader* shader)
{
    if (pipelineSettings.vertexShader != shader)
    {
        pipelineSettings.vertexShader = shader;
        pipelineState = nullptr;
    }
}

void Effect::setPixelShader(Shader* shader)
{
    if (pipelineSettings.pixelShader != shader)
    {
        pipelineSettings.pixelShader = shader;
        pipelineState = nullptr;
    }
}

PipelineState* Effect::getPipelineState()
{
    if (pipelineState == nullptr)
    {
        auto it = states.find_value(pipelineSettings);
        if (it)
        {
            pipelineState = *it;
        }
        else
        {
            auto& renderSystem = App::GetInstance().render_system;
            pipelineState = new PipelineState(renderSystem, pipelineSettings);
            states[pipelineSettings] = pipelineState;
        }
    }

    return pipelineState;
}
