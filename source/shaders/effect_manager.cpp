module effect_manager;

import shader_manager;
import asset_path;

void EffectManager::init()
{
    auto& shaderManager = ShaderManager::GetInstance();

    {
        auto effect = std::make_shared<Effect>();
        AssetPath path = "shaders/shadersTextured.hlsl";
        effect->setVertexShader(shaderManager.getVertexShader(path, "VSMain"));
        effect->setPixelShader(shaderManager.getPixelShader(path, "PSMain"));
        Effects["standard"] = effect;
    }

    {
        auto effect = std::make_shared<Effect>();
        AssetPath path = "shaders/grid.hlsl";
        effect->setVertexShader(shaderManager.getVertexShader(path, "VSMain"));
        effect->setPixelShader(shaderManager.getPixelShader(path, "PSMain"));
        Effects["grid"] = effect;
    }

    {
        auto effect = std::make_shared<Effect>();
        AssetPath path = "shaders/imgui.hlsl";
        effect->setPipelineType(PipelineType::Imgui);
        effect->setVertexShader(shaderManager.getVertexShader(path, "VSMain"));
        effect->setPixelShader(shaderManager.getPixelShader(path, "PSMain"));
        Effects["imgui"] = effect;
    }

    {
        auto effect = std::make_shared<Effect>();
        effect->setPipelineType(PipelineType::Imgui);
        effect->setVertexShader(shaderManager.getVertexShader("shaders/imgui.hlsl", "VSMain"));
        effect->setPixelShader(shaderManager.getPixelShader("shaders/imgui_custom.hlsl", "PSMain"));
        Effects["imgui_custom"] = effect;
    }
}