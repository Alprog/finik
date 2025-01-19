module effect;

import pipeline_state;
import app;
import shader;

HashMap<PipelineSettings, PipelineState*> states;

void Effect::setVertexShader(std::shared_ptr<Shader> shader)
{
    if (vertexShader != shader)
    {
        vertexShader = shader;
        resetPso();
    }
}

void Effect::setPixelShader(std::shared_ptr<Shader> shader)
{
    if (pixelShader != shader)
    {
        pixelShader = shader;
        resetPso();
    }
}

PipelineState* Effect::getPipelineState()
{
    if (pipelineState == nullptr)
    {
        PipelineSettings settings(vertexShader->bytecode, pixelShader->bytecode);

        auto it = states.find_value(settings);
        if (it)
        {
            pipelineState = *it;
        }
        else
        {
            auto& renderSystem = App::GetInstance().render_system;
            pipelineState = new PipelineState(renderSystem, settings);
            states[settings] = pipelineState;
        }
    }

    return pipelineState;
}
