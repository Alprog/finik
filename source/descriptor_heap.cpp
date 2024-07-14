#include "descriptor_heap.h"
#include <stdio.h>

DescriptorHeap::DescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT maxCount)
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.NumDescriptors = maxCount;
    desc.Type = type;    
    const bool shaderVisible = type == D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    this->descriptorCount = 0;
    this->maxCount = maxCount;

    auto result = device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&heap));
    if (FAILED(result)) throw;

    cpuStartHandle = heap->GetCPUDescriptorHandleForHeapStart();
    if (shaderVisible)
    {
        gpuStartHandle = heap->GetGPUDescriptorHandleForHeapStart();
    }
    handleIncrementSize = device->GetDescriptorHandleIncrementSize(desc.Type);
}

DescriptorHandle DescriptorHeap::getNextHandle()
{
    return DescriptorHandle(this, descriptorCount++);
}
