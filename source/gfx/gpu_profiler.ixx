module;
#include "dx.h"
export module gpu_profiler;

import std;
import render_system_fwd;
import dx;

export struct StampRange
{
    int count() const { return endIndex - startIndex; }

    int startIndex = 0;
    int endIndex = 0;
    int readyFenceValue = 0;
};

export class GpuProfiler
{
public:
    GpuProfiler(RenderSystem& renderSystem);

    int addStamp(ID3D12GraphicsCommandList& commandList, void* name);
    void scheduleFrameResolve(ID3D12GraphicsCommandList& commandList);
    void endFrameRange(int readyFenceValue);

    void grabReadyStamps(int completedValue);

private:
    ComPtr<ID3D12QueryHeap> queryHeap;
    ComPtr<ID3D12Resource> readBackBuffer;

    StampRange currentRange;
    std::queue<StampRange> queue;
    UINT64 ticksInMicrosecond;

    UINT64 syncedGpuTimestamp;
    UINT64 syncedCpuTimestamp;
    UINT64 syncedCpuMicroseconds;
};