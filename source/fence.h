#pragma once

#include "dx.h"

class RenderSystem;

class Fence
{
public:
    Fence(RenderSystem& renderSystem);

    int SignalNext(ID3D12CommandQueue& queue);
    int GetLastSignaledValue();
    void WaitForValue(int value);

private:
    ComPtr<ID3D12Fence> FenceImpl;
    HANDLE FenceEvent = nullptr;
    int LastSignaledValue = 0;
};