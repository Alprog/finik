#include "fence.h"

#include "render_system.h"
#include "log.h"
#include "timer.h"

Fence::Fence(RenderSystem& renderSystem, ID3D12CommandQueue& queue)
    : Queue { queue }
{
    auto result = renderSystem.get_device()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&FenceImpl));
    if (FAILED(result)) throw;

    FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!FenceEvent) throw;
}

int Fence::SignalNext()
{
    Queue.Signal(FenceImpl.Get(), ++LastSignaledValue);
    return LastSignaledValue;
}

int Fence::GetLastSignaledValue()
{
    return LastSignaledValue;
}

int Fence::GetCompletedValue()
{
    return FenceImpl->GetCompletedValue();
}

void Fence::WaitForValue(int value)
{
    if (value != 0)
    {
        FenceImpl->SetEventOnCompletion(value, FenceEvent);
        WaitForSingleObject(FenceEvent, INFINITE);
    }
}