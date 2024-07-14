#include "render_context.h"

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "render_state.h"
#include "render_command.h"
#include "mesh.h"

RenderContext::RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList)
    : renderSystem{ renderSystem }
    , commandList{ commandList }
{
}

void RenderContext::draw(RenderCommand renderCommand)
{
    auto mesh = renderCommand.mesh;
    auto texture = renderCommand.state->texture;
    //auto cbImpl = getImpl(renderCommand.state->constantBuffer);
    //cbImpl->update();

    //commandList.SetGraphicsRootDescriptorTable(0, getImpl(texture)->descriptorHandle.getGPU());
    //commandList.SetGraphicsRootDescriptorTable(1, cbImpl->descriptorHandle.getGPU());

    commandList.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    commandList.IASetVertexBuffers(0, 1, &renderCommand.mesh->vertexBuffer->vertexBufferView);
    commandList.IASetIndexBuffer(&renderCommand.mesh->indexBuffer->indexBufferView);

    commandList.DrawIndexedInstanced(36, 1, 0, 0, 0);
}