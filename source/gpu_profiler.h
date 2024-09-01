#pragma once

#include "dx.h"
#include <queue>

class RenderSystem;

struct StampRange
{
    int count() const { return endIndex - startIndex; }

    int startIndex = 0;
    int endIndex = 0;
    int readyFenceValue = 0;
};

class GpuProfiler
{
public:
    GpuProfiler(RenderSystem& renderSystem);

    void addStamp(ID3D12GraphicsCommandList& commandList, void* name);
    void scheduleFrameResolve(ID3D12GraphicsCommandList& commandList);
    void endFrameRange(int readyFenceValue);

    void grabReadyStamps(int fenceValue);

private:
    ComPtr<ID3D12QueryHeap> queryHeap;
    ComPtr<ID3D12Resource> readBackBuffer;

    StampRange currentRange;
    std::queue<StampRange> queue;
};