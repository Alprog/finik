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
import shader_manager;

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
    RenderSystem& renderSystem = App::GetInstance().render_system;

    int32 frameIndex = App::GetInstance().getFrameIndex();
    int32 size = sizeof(FrameConstantBuffer::data);


    auto frameConstantBuffer = renderSystem.getOneshotAllocator().Allocate<FrameConstants>();

    
    auto& ShaderManager = ShaderManager::GetInstance();

    if (!renderCommand.state)
    {
        renderCommand.mesh = createCubeMesh();

        AssetPath path = "shaders/shadersTextured.hlsl";
        renderCommand.state = new RenderState();
        renderCommand.state->setVertexShader(ShaderManager.getVertexShader(path, "VSMain"));
        renderCommand.state->setPixelShader(ShaderManager.getPixelShader(path, "PSMain"));
    }

    if (!renderCommand2.state)
    {
        renderCommand2.mesh = grid->mesh;

        AssetPath path = "shaders/grid.hlsl";
        renderCommand2.state = new RenderState();       
        renderCommand2.state->setVertexShader(ShaderManager.getVertexShader(path, "VSMain"));
        renderCommand2.state->setPixelShader(ShaderManager.getPixelShader(path, "PSMain"));
    }

    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;
    

    frameConstantBuffer->ViewProjection = V * P;

    actors[0]->transformMatrix = Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.0f));
    actors[1]->transformMatrix = Matrix::Translation(Vector3(0.0f, 0.0f, 1.0f));

    //----------------------------------------------------

    auto mesh = renderCommand.mesh;
    auto& commandList = renderContext.commandList;

    commandList.SetGraphicsRootSignature(renderSystem.getRootSignature().signatureImpl.Get());
    
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

    //----------------------

    commandList.SetPipelineState(renderCommand2.state->getPipelineState()->pipelineState.Get());
    renderContext.setMaterial(*grid->material);

    renderContext.setModelMatrix(Matrix::Identity);
    renderContext.drawMesh(renderCommand2.mesh);

}