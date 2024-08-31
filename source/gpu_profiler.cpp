#include "gpu_profiler.h"

#include "render_system.h"

int constexpr MAX_TIMESTAMP = 100;

GpuProfiler::GpuProfiler(RenderSystem& renderSystem)
{
    D3D12_QUERY_HEAP_DESC queryHeapDesc = {};
    queryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
    queryHeapDesc.Count = MAX_TIMESTAMP;
    queryHeapDesc.NodeMask = 0;

    renderSystem.get_device()->CreateQueryHeap(&queryHeapDesc, IID_PPV_ARGS(&queryHeap));

    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferDesc.Width = sizeof(UINT64) * MAX_TIMESTAMP; // Two timestamps
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
        IID_PPV_ARGS(&resultBuffer));
}

void GpuProfiler::addStamp(ID3D12GraphicsCommandList& commandList, void* name)
{
    commandList.EndQuery(queryHeap.Get(), D3D12_QUERY_TYPE_TIMESTAMP, index++ % MAX_TIMESTAMP);
}