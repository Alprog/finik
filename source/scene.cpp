module scene;

import app;
import render_system;
import effect;
import mesh;
import constant_buffer;
import texture;
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
import effect_manager;

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


    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;
    

    frameConstantBuffer->ViewProjection = V * P;

    actors[0]->transformMatrix = Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.0f));
    actors[1]->transformMatrix = Matrix::Translation(Vector3(0.0f, 0.0f, 1.0f));

    //----------------------------------------------------

    auto& commandList = renderContext.commandList;

    commandList.SetGraphicsRootSignature(renderSystem.getRootSignature().signatureImpl.Get());
    
    auto address = MaterialManager::GetInstance().ConstantBuffer->uploadBuffer->GetGPUVirtualAddress();
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MaterialsConstantBufferView, address);
    
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::FrameConstantBufferView, frameConstantBuffer.GpuAddress);
    
    CD3DX12_GPU_DESCRIPTOR_HANDLE startHandle = renderSystem.getSrvCbvHeap()->getGpuHandle(0);
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::UnboundTextureTable, startHandle);

    commandList.SetPipelineState(EffectManager::GetInstance().get("standard")->getPipelineState()->pipelineState.Get());

    for (auto& actor : actors)
    {
        renderContext.setModelMatrix(actor->transformMatrix);
        renderContext.setMaterial(*actor->material);
        renderContext.drawMesh(actor->mesh);
    }

    //----------------------

    commandList.SetPipelineState(EffectManager::GetInstance().get("grid")->getPipelineState()->pipelineState.Get());
    renderContext.setMaterial(*grid->material);

    renderContext.setModelMatrix(Matrix::Identity);
    renderContext.drawMesh(grid->mesh);

}