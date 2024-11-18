module scene;

import app;
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
import descriptor_heap;
import material_manager;
import upload_buffer;

Scene::Scene()
{
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

GpuFrameConstantBuffer* getConstantBuffer(Camera* camera)
{
    static std::unordered_map<Camera*, GpuFrameConstantBuffer*> maps[5];

    auto frameIndex = App::GetInstance().profiler.getFrameIndex();
    auto& constantBuffers = maps[frameIndex % 5];

    auto it = constantBuffers.find(camera);
    if (it != constantBuffers.end())
    {
        return it->second;
    }

    auto& renderSystem = App::GetInstance().render_system;
    auto constantBuffer = new GpuFrameConstantBuffer(renderSystem);
    constantBuffers[camera] = constantBuffer;
    return constantBuffer;
}

void Scene::render(RenderContext& renderContext, Camera* camera)
{
    RenderSystem& renderSystem = App::GetInstance().render_system;

    int32 frameIndex = App::GetInstance().getFrameIndex();
    int32 size = sizeof(GpuFrameConstantBuffer::data);


    auto frameConstantBuffer = renderSystem.getOneshotAllocator().Allocate<FrameConstantBuffer>();

    GpuFrameConstantBuffer* constantBuffer = getConstantBuffer(camera);

    if (!renderCommand.state)
    {
        renderCommand.mesh = createCubeMesh();

        auto path = "C:/finik/shaders/shadersTextured.hlsl";
        renderCommand.state = new RenderState();
        renderCommand.state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        renderCommand.state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));
    }

    if (!renderCommand2.state)
    {
        renderCommand2.mesh = grid->mesh;

        auto path = "C:/finik/shaders/grid.hlsl";
        renderCommand2.state = new RenderState();       
        renderCommand2.state->setVertexShader(new Shader(path, ShaderType::Vertex, "VSMain"));
        renderCommand2.state->setPixelShader(new Shader(path, ShaderType::Pixel, "PSMain"));
    }

    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;
    (*constantBuffer)->ViewProjection = V * P;


    frameConstantBuffer->ViewProjection = V * P;

    renderCommand2.state->constantBuffer = constantBuffer;
    renderCommand2.state->constantBuffer = constantBuffer;

    actors[0]->transformMatrix = Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.0f));
    actors[1]->transformMatrix = Matrix::Translation(Vector3(0.0f, 0.0f, 1.0f));

    //----------------------------------------------------

    auto mesh = renderCommand.mesh;
    auto& commandList = renderContext.commandList;
    commandList.SetGraphicsRootSignature(renderCommand.state->getPipelineState()->rootSignature.Get());
    
    auto address = MaterialManager::GetInstance().ConstantBuffer->uploadBuffer->GetGPUVirtualAddress();
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MaterialsConstantBufferView, address);
    
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::FrameConstantBufferView, frameConstantBuffer.GpuAddress);
    
    CD3DX12_GPU_DESCRIPTOR_HANDLE startHandle = renderSystem.getSrvCbvHeap()->getGpuHandle(0);
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::UnboundTextureTable, startHandle);

    commandList.SetPipelineState(renderCommand.state->getPipelineState()->pipelineState.Get());

    for (auto& actor : actors)
    {
        renderContext.setModelMatrix(actor->transformMatrix);
        renderContext.setMaterial(*actor->material);
        renderContext.drawMesh(actor->mesh);
    }

    renderContext.setMaterial(*grid->material);
    renderContext.draw(renderCommand2);
}