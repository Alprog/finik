module render_state;

import pipeline_state;
import app;
import shader;

std::unordered_map<PipelineSettings, PipelineState*> states;

RenderState::RenderState()
    : constantBuffer {nullptr}
{
}

void RenderState::setVertexShader(Shader* shader)
{
    if (pipelineSettings.vertexShader != shader)
    {
        pipelineSettings.vertexShader = shader;
        pipelineState = nullptr;
    }
}

void RenderState::setPixelShader(Shader* shader)
{
    if (pipelineSettings.pixelShader != shader)
    {
        pipelineSettings.pixelShader = shader;
        pipelineState = nullptr;
    }
}

PipelineState* RenderState::getPipelineState()
{
    if (pipelineState == nullptr)
    {
        auto it = states.find(pipelineSettings);
        if (it != states.end())
        {
            pipelineState = it->second;
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
