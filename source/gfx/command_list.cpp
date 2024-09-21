#include "command_list.h"

#include "render_system.h"
#include "command_list_pool.h"
#include "gpu_profiler.h"

CommandList::CommandList(RenderSystem& renderSystem, CommandListPool& pool, const int frameIndex)
    : renderSystem{ renderSystem }
    , pool { pool }
    , frameIndex { frameIndex }
{
    auto device = renderSystem.get_device();

    auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(result)) throw;

    result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&listImpl));
    if (FAILED(result)) throw;

    // open and ready to record
}

void CommandList::reset(const int frameIndex)
{
    commandAllocator->Reset();
    listImpl->Reset(commandAllocator.Get(), nullptr);
    this->frameIndex = frameIndex;
}

void CommandList::returnToPool()
{
    frameIndex = 0;
    pool.putBack(*this);
}

int CommandList::getFrameIndex() const
{
    return frameIndex;
}

void CommandList::startRecording()
{
    startTimestampIndex = addTimestampQuery();
}

void CommandList::endRecording()
{
    endTimestampIndex = addTimestampQuery();
    listImpl->Close();
}

int CommandList::addTimestampQuery()
{
    return renderSystem.getProfiler()->addStamp(*listImpl.Get(), "list");
}
