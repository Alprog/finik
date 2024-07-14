#include "scene.h"

#include "shader.h"
#include "render_command.h"
#include "app.h"
#include "render_system.h"
#include "render_state.h"
#include "mesh.h"

Scene::Scene()
{
}

void Scene::render(RenderContext& renderContext)
{
    auto path = "C:/finik/source/shadersTextured.hlsl";

    static PipelineState* state;

    if (!state)
    {
        auto& renderSystem = App::get_instance().render_system;

        RenderState* state = new RenderState();
        state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));

        renderCommand.mesh = createCubeMesh();
        renderCommand.state = state;
    }

    renderContext.draw(renderCommand);
}