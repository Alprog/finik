module render_context;

import constant_buffer;
import pipeline_state;
import render_system;
import root_signature_params;
import mesh;
import effect;
import material_manager;
import upload_buffer;
import descriptor_heap;

RenderContext::RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList)
    : renderSystem{ renderSystem }
    , commandList{ commandList }
{
}

void RenderContext::setupRoot()
{
    commandList.SetGraphicsRootSignature(renderSystem.getRootSignature().signatureImpl.Get());

    auto address = MaterialManager::GetInstance().ConstantBuffer->uploadBuffer->GetGPUVirtualAddress();
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MaterialsConstantBufferView, address);

    CD3DX12_GPU_DESCRIPTOR_HANDLE startHandle = renderSystem.getSrvCbvHeap()->getGpuHandle(0);
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::UnboundTextureTable, startHandle);
}

void RenderContext::setFrameConstants(D3D12_GPU_VIRTUAL_ADDRESS gpuAddress)
{
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::FrameConstantBufferView, gpuAddress);
}

void RenderContext::setModelMatrix(const Matrix& matrix)
{
    auto meshConstantBuffer = renderSystem.getOneshotAllocator().Allocate<MeshConstants>();
    meshConstantBuffer.Data->Model = matrix;

    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MeshConstantBufferView, meshConstantBuffer.GpuAddress);
}

void RenderContext::setMaterial(const Material& material)
{
    commandList.SetPipelineState(material.Effect->getPipelineState()->pipelineState.Get()); // set effect
    commandList.SetGraphicsRoot32BitConstant(RootSignatureParams::MaterialInlineConstants, material.Index, 0);
}

void RenderContext::drawMesh(Mesh* mesh)
{
    commandList.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList.IASetVertexBuffers(0, 1, &mesh->vertexBuffer->vertexBufferView);
    commandList.IASetIndexBuffer(&mesh->indexBuffer->indexBufferView);

    commandList.DrawIndexedInstanced(mesh->indexBuffer->indices.count(), 1, 0, 0, 0);
}
