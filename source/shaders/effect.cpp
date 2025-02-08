module effect;

import render_system;
import shader;
import pso_manager;

void Effect::setPipelineType(PipelineType type)
{
    if (this->type != type)
    {
        this->type = type;
        resetPso();
    }
}

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

MyPtr<ID3D12PipelineState> Effect::getPipelineState()
{
    if (pipelineState.Get() == nullptr)
    {
        PipelineSettings settings(vertexShader->bytecode, pixelShader->bytecode);
        settings.type = type;
        pipelineState = Single::Get<PSOManager>().get_pso(settings);
    }

    return pipelineState;
}
