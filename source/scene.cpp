#include "scene.h"

#include "shader.h"
#include "render_command.h"
#include "app.h"
#include "render_system.h"
#include "render_state.h"
#include "mesh.h"
#include "constant_buffer.h"
#include "math/matrix.h"

Scene::Scene()
{
}

void Scene::update(float deltaTime)
{
    static float angle = 0;
    angle += deltaTime;

    if (renderCommand.state)
    {
        auto M = Matrix::RotationX(-3.14f / 4) * Matrix::RotationY(angle) * Matrix::Translation(Vector3(0, 0, 0.5f));
        auto V = Matrix::Identity;
        auto P = Matrix::Identity;

        renderCommand.state->constantBuffer->data.MVP = M * V * P;
        renderCommand.state->constantBuffer->version++;
    }
}

void Scene::render(RenderContext& renderContext)
{
    auto path = "C:/finik/source/shadersTextured.hlsl";

    if (!renderCommand.state)
    {
        auto& renderSystem = App::get_instance().render_system;

        renderCommand.mesh = createCubeMesh();

        renderCommand.state = new RenderState();
        renderCommand.state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        renderCommand.state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));

        auto constantBuffer = new ConstantBuffer(renderSystem);
        constantBuffer->data.MVP = Matrix::Identity;
        constantBuffer->version++;

        renderCommand.state->constantBuffer = constantBuffer;
    }

    renderContext.draw(renderCommand);
}