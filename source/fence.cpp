#include "fence.h"

#include "render_system.h"

Fence::Fence(RenderSystem& renderSystem)
{
    auto result = renderSystem.get_device()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&FenceImpl));
    if (FAILED(result)) throw;

    FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!FenceEvent) throw;
}

int Fence::SignalNext(ID3D12CommandQueue& queue)
{
    queue.Signal(FenceImpl.Get(), ++LastSignaledValue);
    return LastSignaledValue;
}

int Fence::GetLastSignaledValue()
{
    return LastSignaledValue;
}

void Fence::WaitForValue(int value)
{
    if (value != 0)
    {
        FenceImpl->SetEventOnCompletion(value, FenceEvent);
        WaitForSingleObject(FenceEvent, INFINITE);
    }
}