module render_context;

import constant_buffer;
import pipeline_state;
import render_system;

RenderContext::RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList)
    : renderSystem{ renderSystem }
    , commandList{ commandList }
{
}

void RenderContext::draw(RenderCommand renderCommand)
{
    auto mesh = renderCommand.mesh;
    ConstantBuffer* constantBuffer = renderCommand.state->constantBuffer;
    constantBuffer->update();

    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView1, renderCommand.texture->descriptorHandle.getGPU());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView2, renderCommand.texture2->descriptorHandle.getGPU());

    uint32 TextureId = renderCommand.texture2->descriptorHandle.getIndex();
    commandList.SetGraphicsRoot32BitConstant(RootSignatureParams::MaterialInlineConstants, TextureId, 0);

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

    commandList.DrawIndexedInstanced(mesh->indexBuffer->indices.size(), 1, 0, 0, 0);
}

void RenderContext::setModelMatrix(const Matrix& matrix)
{
    auto meshConstantBuffer = renderSystem.getOneshotAllocator().Allocate<MeshConstantBuffer>();
    meshConstantBuffer.Data->Model = matrix;

    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::MeshConstantBufferView, meshConstantBuffer.GpuAddress);
}