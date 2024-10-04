module;
#include "dx.h"
export module fence;

import dx;
import render_system_fwd;

export class Fence
{
public:
    Fence(RenderSystem& renderSystem, ID3D12CommandQueue& queue);

    int SignalNext();
    int GetLastSignaledValue();
    int GetCompletedValue();
    void WaitForValue(int value);

private:
    ID3D12CommandQueue& Queue;
    ComPtr<ID3D12Fence> FenceImpl;
    HANDLE FenceEvent = nullptr;
    int LastSignaledValue = 0;
};