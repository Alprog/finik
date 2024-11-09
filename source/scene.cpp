module scene;

import app;
import math;
import render_system;
import render_state;
import mesh;
import constant_buffer;
import texture;
import render_command;
import root_signature_params;
import actor;
import shader;
import grid;
import camera;
import oneshot_allocator;
import allocation;

Scene::Scene()
{
    texture = new Texture("C:/finik/source/skullbox.png");
    cellTexture = new Texture("C:/finik/source/cell.png");
    grid = new Grid();

    actors.push_back(new Actor());
    actors.push_back(new Actor());
}

void Scene::update(float deltaTime)
{
    static float angle = 0;
    angle += deltaTime;

    if (renderCommand.state)
    {
        //auto M = Matrix::RotationX(-3.14f / 4) * Matrix::RotationY(angle) * Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.5f));
        //auto V = Matrix::Identity;
        //auto P = Matrix::Identity;

        //renderCommand.state->constantBuffer->data.MVP = M * V * P;
        //renderCommand.state->constantBuffer->version++;
    }
}

ConstantBuffer* getConstantBuffer(Camera* camera)
{
    static std::unordered_map<Camera*, ConstantBuffer*> maps[5];

    auto frameIndex = App::get_instance().profiler.getFrameIndex();
    auto& constantBuffers = maps[frameIndex % 5];

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
    auto& renderSystem = App::get_instance().render_system;

    int32 frameIndex = App::get_instance().getFrameIndex();
    int32 size = sizeof(ConstantBuffer::data);

    finik::gpumem::Allocation allocation = renderSystem.getOneshotAllocator().Allocate(size, frameIndex);
    ConstantBuffer* constantBuffer = getConstantBuffer(camera);

    if (!renderCommand.state)
    {
        renderCommand.mesh = createCubeMesh();

        auto path = "C:/finik/source/shadersTextured.hlsl";
        renderCommand.state = new RenderState();
        renderCommand.state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        renderCommand.state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));
        renderCommand.texture = texture;
        renderCommand.texture2 = grid->tileMap->Texture;
    }

    if (!renderCommand2.state)
    {
        renderCommand2.mesh = grid->mesh;

        auto path = "C:/finik/source/grid.hlsl";
        renderCommand2.state = new RenderState();       
        renderCommand2.state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        renderCommand2.state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));
        renderCommand2.texture = cellTexture;
        renderCommand2.texture2 = grid->tileMap->Texture;
    }

    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;
    constantBuffer->data.ViewProjection = V * P;
    constantBuffer->version++;
    constantBuffer->update();

    renderCommand2.state->constantBuffer = constantBuffer;
    renderCommand2.state->constantBuffer = constantBuffer;
    renderContext.draw(renderCommand2);

    actors[0]->transformMatrix = Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.0f));
    actors[1]->transformMatrix = Matrix::Translation(Vector3(0.0f, 0.0f, 1.0f));

    //----------------------------------------------------

    auto mesh = renderCommand.mesh;
    auto& commandList = renderContext.commandList;
    commandList.SetGraphicsRootSignature(renderCommand.state->getPipelineState()->rootSignature.Get());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::FrameConstantBufferView, constantBuffer->descriptorHandle.getGPU());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView1, renderCommand.texture->descriptorHandle.getGPU());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView2, renderCommand.texture2->descriptorHandle.getGPU());

    commandList.SetPipelineState(renderCommand.state->getPipelineState()->pipelineState.Get());


    for (auto& actor : actors)
    {
        renderContext.setModelMatrix(actor->transformMatrix);
        renderContext.drawMesh(actor->mesh);
    }
}