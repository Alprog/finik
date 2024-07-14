#include "render_state.h"

#include "shader.h"
#include <vector>
#include <unordered_map>
#include "pipeline_state.h"
#include "app.h"

std::unordered_map<PipelineSettings, PipelineState*> states;

RenderState::RenderState()
    : texture {nullptr}
    , constantBuffer {nullptr}
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
            auto& renderSystem = App::get_instance().render_system;
            pipelineState = new PipelineState(renderSystem, pipelineSettings);
            states[pipelineSettings] = pipelineState;
        }
    }

    return pipelineState;
}
