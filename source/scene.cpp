module scene;

import render_system;
import effect;
import mesh;
import texture;
import actor;
import shader;
import grid;
import camera;
import oneshot_allocator;
import allocation;
import effect_manager;
import root_signature_params;
import render_context;

Scene::Scene()
{
    grid = new Grid();

    actors.append(new Actor());
    actors.append(new Actor());
}

void Scene::update(float deltaTime)
{
    static float angle = 0;
    angle += deltaTime;
}

void Scene::render(RenderContext& renderContext, Camera* camera)
{
    actors[0]->transformMatrix = Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.0f));
    actors[1]->transformMatrix = Matrix::Translation(Vector3(0.0f, 0.0f, 1.0f));

    //----------------------------------------------------

    renderContext.setupRoot();

    auto frameConstants = renderContext.renderSystem.getOneshotAllocator().Allocate<FrameConstants>();
    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;
    frameConstants->ViewProjection = V * P;
    renderContext.setFrameConstants(frameConstants.GpuAddress);

    //----------------------

    for (auto& actor : actors)
    {
        renderContext.setModelMatrix(actor->transformMatrix);
        renderContext.setMaterial(*actor->material);
        renderContext.drawMesh(actor->mesh);
    }

    //----------------------

    renderContext.setModelMatrix(Matrix::Identity);
    renderContext.setMaterial(*grid->material);
    renderContext.drawMesh(grid->mesh);
}