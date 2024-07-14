#include "scene.h"

Scene::Scene()
{
    mesh = createCubeMesh();
}

void Scene::render(RenderContext& context)
{
    //auto path = "C:/finik/source/shadersTextured.hlsl";
    //Shader vertexShader(path, ShaderType::Vertex, "VSMain");
    //Shader pixelShader(path, ShaderType::Pixel, "PSMain");

}