module shader_manager;

const char* ShaderManager::getFallbackVertexShaderText()
{
    return "\
        float4 VSMain(float3 position : POSITION) : SV_POSITION \
        {\
            return float4(position, 1);\
        }\
        ";
}

const char* ShaderManager::getFallbackPixelShaderText()
{
    return "float4 PSMain() : SV_TARGET { return 1; }";
}