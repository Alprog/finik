#include "gpu_profiler.h"

#include "render_system.h"
#include <cassert>

int constexpr MAX_TIMESTAMP = 100;
int constexpr readBackRecordSize = sizeof(UINT64);

GpuProfiler::GpuProfiler(RenderSystem& renderSystem)
{
    D3D12_QUERY_HEAP_DESC queryHeapDesc = {};
    queryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
    queryHeapDesc.Count = MAX_TIMESTAMP;
    queryHeapDesc.NodeMask = 0;

    renderSystem.get_device()->CreateQueryHeap(&queryHeapDesc, IID_PPV_ARGS(&queryHeap));

    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferDesc.Width = readBackRecordSize * MAX_TIMESTAMP; // Two timestamps
    bufferDesc.Height = 1;
    bufferDesc.DepthOrArraySize = 1;
    bufferDesc.MipLevels = 1;
    bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    bufferDesc.SampleDesc.Count = 1;
    bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_READBACK;

    renderSystem.get_device()->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&readBackBuffer));
}

void GpuProfiler::addStamp(ID3D12GraphicsCommandList& commandList, void* name)
{
    int index = currentRange.endIndex++ % MAX_TIMESTAMP;
    commandList.EndQuery(queryHeap.Get(), D3D12_QUERY_TYPE_TIMESTAMP, index);
}

void GpuProfiler::scheduleFrameResolve(ID3D12GraphicsCommandList& commandList)
{
    assert(currentRange.count() <= MAX_TIMESTAMP);

    auto resolveHelper = [&commandList, this](int start, int end)
    {
        int count = end - start;
        if (count > 0)
        {
            auto type = D3D12_QUERY_TYPE_TIMESTAMP;
            int offset = start * readBackRecordSize;
            commandList.ResolveQueryData(queryHeap.Get(), type, start, count, readBackBuffer.Get(), offset);
        }
    };

    int start = currentRange.startIndex % MAX_TIMESTAMP;
    int end = currentRange.endIndex % MAX_TIMESTAMP;
    if (start < end)
    {
        resolveHelper(start, end);
    }
    else
    {
        resolveHelper(0, end);
        resolveHelper(start, MAX_TIMESTAMP);
    }    
}

void GpuProfiler::endFrameRange(const int readyFenceValue)
{
    currentRange.readyFenceValue = readyFenceValue;
    queue.push(currentRange);
    currentRange = { currentRange.endIndex, currentRange.endIndex, 0 };
}

void GpuProfiler::grabReadyStamps(int fenceValue)
{
    while (queue.front().readyFenceValue <= fenceValue)
    {
        queue.pop();
    }
}