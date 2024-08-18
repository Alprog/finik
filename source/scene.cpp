#include "scene.h"

#include "shader.h"
#include "render_command.h"
#include "app.h"
#include "render_system.h"
#include "render_state.h"
#include "mesh.h"
#include "constant_buffer.h"
#include "math/matrix.h"
#include "camera.h"
#include "texture.h"
#include "tile_map.h"

Scene::Scene()
{
    texture = new Texture("C:/finik/source/skullbox.png");
    tileMap = new TileMap();
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

ConstantBuffer* getConstantBuffer(Camera* camera)
{
    static std::unordered_map<Camera*, ConstantBuffer*> constantBuffers;
    auto it = constantBuffers.find(camera);
    if (it != constantBuffers.end())
    {
        return it->second;
    }

    auto& renderSystem = App::get_instance().render_system;
    auto constantBuffer = new ConstantBuffer(renderSystem);
    constantBuffers[camera] = constantBuffer;
    return constantBuffer;
}

void Scene::render(RenderContext& renderContext, Camera* camera)
{
    auto path = "C:/finik/source/shadersTextured.hlsl";

    if (!renderCommand.state)
    {
        renderCommand.mesh = createCubeMesh();

        renderCommand.state = new RenderState();
        renderCommand.state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        renderCommand.state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));
        renderCommand.texture = texture;
    }

    renderCommand.state->constantBuffer = getConstantBuffer(camera);

    auto M = Matrix::Identity;
    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;

    renderCommand.state->constantBuffer->data.MVP = M * V * P;
    renderCommand.state->constantBuffer->version++;

    renderContext.draw(renderCommand);
}