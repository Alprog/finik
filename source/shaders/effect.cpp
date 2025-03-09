module effect;

import render_system;
import shader;
import pso_manager;
import shader_manager;

Effect::Effect(String name)
    : name{name}
{
}

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

std::shared_ptr<PipelineState> Effect::getPipelineState()
{
    if (pipelineState == nullptr)
    {
        auto pixelBytecode = pixelShader ? pixelShader->bytecode : ShaderManager::GetInstance().getFallbackByteCode(ShaderType::Pixel);
        PipelineSettings settings(vertexShader->bytecode, pixelBytecode);
        settings.type = type;
        pipelineState = Single::Get<PSOManager>().get_pso(settings);
    }

    return pipelineState;
}
