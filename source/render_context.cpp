#include "render_context.h"

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "render_state.h"
#include "render_command.h"
#include "pipeline_state.h"
#include "mesh.h"
#include "constant_buffer.h"
#include "texture.h"
#include "root_signature_params.h"

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

    Matrix M = Matrix::Identity;
    commandList.SetGraphicsRoot32BitConstants(RootSignatureParams::MeshInlinedConstants, 4, &M, 0);
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::FrameConstantBufferView, constantBuffer->descriptorHandle.getGPU());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView1, renderCommand.texture->descriptorHandle.getGPU());
    commandList.SetGraphicsRootDescriptorTable(RootSignatureParams::TextureView2, renderCommand.texture2->descriptorHandle.getGPU());
    
    commandList.SetPipelineState(renderCommand.state->getPipelineState()->pipelineState.Get());
    commandList.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList.IASetVertexBuffers(0, 1, &renderCommand.mesh->vertexBuffer->vertexBufferView);
    commandList.IASetIndexBuffer(&renderCommand.mesh->indexBuffer->indexBufferView);

    commandList.DrawIndexedInstanced(renderCommand.mesh->indexBuffer->indices.size(), 1, 0, 0, 0);
}