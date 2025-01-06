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


    auto frameConstants = renderSystem.getOneshotAllocator().Allocate<FrameConstants>();


    auto V = camera->viewMatrix;
    auto P = camera->projectionMatrix;
    

    frameConstants->ViewProjection = V * P;

    actors[0]->transformMatrix = Matrix::Translation(Vector3(castedPos.x, castedPos.y, 0.0f));
    actors[1]->transformMatrix = Matrix::Translation(Vector3(0.0f, 0.0f, 1.0f));

    //----------------------------------------------------

    auto& commandList = renderContext.commandList;

    commandList.SetGraphicsRootSignature(renderSystem.getRootSignature().signatureImpl.Get());
    
    auto address = MaterialManager::GetInstance().ConstantBuffer->uploadBuffer->GetGPUVirtualAddress();
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MaterialsConstantBufferView, address);
       
    CD3DX12_GPU_DESCRIPTOR_HANDLE startHandle = renderSystem.getSrvCbvHeap()->getGpuHandle(0);
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::UnboundTextureTable, startHandle);

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