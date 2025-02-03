module effect;

import render_system;
import shader;
import pso_manager;

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
        pipelineState = Single::Get<PSOManager>().get_pso(settings);
    }

    return pipelineState;
}
