module render_context;

import vertex_buffer;
import index_buffer;
import render_state;
import pipeline_state;
import mesh;
import constant_buffer;
import texture;
import render_command;
import root_signature_params;
import app;

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

    int32 frameIndex = App::get_instance().getFrameIndex();
    auto frameConstantBuffer = renderSystem.getOneshotAllocator().Allocate<FrameConstantBuffer>(frameIndex);
    *frameConstantBuffer.Data = constantBuffer->data;

    PipelineState* pipeline = renderCommand.state->getPipelineState();
    commandList.SetGraphicsRootSignature(pipeline->rootSignature.Get());
    commandList.SetGraphicsRootConstantBufferView(RootSignatureParams::FrameConstantBufferView, frameConstantBuffer.GpuAddress);
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView1, renderCommand.texture->descriptorHandle.getGPU());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView2, renderCommand.texture2->descriptorHandle.getGPU());
    
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
    commandList.SetGraphicsRoot32BitConstants(RootSignatureParams::MeshInlinedConstants, 16, &matrix, 0);
}