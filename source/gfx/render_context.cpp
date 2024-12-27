module render_context;

import constant_buffer;
import pipeline_state;
import render_system;
import root_signature_params;

RenderContext::RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList)
    : renderSystem{ renderSystem }
    , commandList{ commandList }
{
}

void RenderContext::draw(RenderCommand renderCommand)
{
    auto mesh = renderCommand.mesh;
    GpuBuffer<FrameConstants>* constantBuffer = renderCommand.state->constantBuffer;
   

    commandList.SetPipelineState(renderCommand.state->getPipelineState()->pipelineState.Get());

    static Matrix Matrix = Matrix::Identity;
    setModelMatrix(Matrix);
    drawMesh(renderCommand.mesh);
}

void RenderContext::drawMesh(Mesh* mesh)
{
    commandList.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList.IASetVertexBuffers(0, 1, &mesh->vertexBuffer->vertexBufferView);
    commandList.IASetIndexBuffer(&mesh->indexBuffer->indexBufferView);

    commandList.DrawIndexedInstanced(mesh->indexBuffer->indices.count(), 1, 0, 0, 0);
}

void RenderContext::setModelMatrix(const Matrix& matrix)
{
    auto meshConstantBuffer = renderSystem.getOneshotAllocator().Allocate<MeshConstants>();
    meshConstantBuffer.Data->Model = matrix;

    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MeshConstantBufferView, meshConstantBuffer.GpuAddress);
}

void RenderContext::setMaterial(const Material& material)
{
    commandList.SetGraphicsRoot32BitConstant(RootSignatureParams::MaterialInlineConstants, material.Index, 0);
}