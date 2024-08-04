#pragma once

#include "dx.h"
#include "fence.h"

class RenderSystem;

class CommandQueue
{
public:
    CommandQueue(RenderSystem& renderSystem);

    ID3D12CommandQueue* operator->();
    int SignalNext();
    void WaitForValue(int value);

    ComPtr<ID3D12CommandQueue> queueImpl;
    std::unique_ptr<Fence> fence;
};