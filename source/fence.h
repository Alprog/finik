#pragma once

#include "dx.h"

class RenderSystem;

class Fence
{
public:
    Fence(RenderSystem& renderSystem, ID3D12CommandQueue& queue);

    int SignalNext();
    int GetLastSignaledValue();
    void WaitForValue(int value);

private:
    ID3D12CommandQueue& Queue;
    ComPtr<ID3D12Fence> FenceImpl;
    HANDLE FenceEvent = nullptr;
    int LastSignaledValue = 0;
};