#include "render_context.h"

#include "render_command.h"
#include "root_signature_params.h"

import vertex_buffer;
import index_buffer;
import render_state;
import pipeline_state;
import mesh;
import constant_buffer;
import texture;

RenderContext::RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList)
    : renderSystem{ renderSystem }
    , commandList{ commandList }
{
}

void RenderContext::draw(RenderCommand renderCommand)
{
    auto mesh = renderCommand.mesh;
    auto constantBuffer = renderCommand.state->constantBuffer;
    constantBuffer->update();

    commandList.SetGraphicsRootSignature(renderCommand.state->getPipelineState()->rootSignature.Get());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::FrameConstantBufferView, constantBuffer->descriptorHandle.getGPU());
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