#include "command_list.h"

#include "render_system.h"
#include "command_list_pool.h"

CommandList::CommandList(RenderSystem& renderSystem, CommandListPool& pool)
    : renderSystem{ renderSystem }
    , pool { pool }
{
    auto device = renderSystem.get_device();

    auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(result)) throw;

    result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&listImpl));
    if (FAILED(result)) throw;

    // open and ready to record
}

void CommandList::reset()
{
    commandAllocator->Reset();
    listImpl->Reset(commandAllocator.Get(), nullptr);
}

void CommandList::returnToPool()
{
    pool.putBack(*this);
}