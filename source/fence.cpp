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

    log("{} SIGNALED: {}/{} \n", get_elapsed_time_string(), FenceImpl->GetCompletedValue(), LastSignaledValue);

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
        log("{} WAIT: {} > {} ({}) \n", get_elapsed_time_string(), FenceImpl->GetCompletedValue(), value, LastSignaledValue);

        FenceImpl->SetEventOnCompletion(value, FenceEvent);
        WaitForSingleObject(FenceEvent, INFINITE);
    }
}