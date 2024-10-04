#include "memory_page.h"

import render_system;

using namespace finik::gpumem;

MemoryPage::MemoryPage(RenderSystem& renderSystem, int size)
    : FullSize{ size }
    , AvailableSize{ size }
    , UsingFrame { 0 }
{
    auto device = renderSystem.get_device();

    auto result = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(size),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&Resource));

    if (FAILED(result)) throw;

    CD3DX12_RANGE readRange(0, 0);
    result = Resource->Map(0, &readRange, reinterpret_cast<void**>(&Data));
    if (FAILED(result)) throw;
}

int MemoryPage::GetFullSize() const
{
    return FullSize;
}

int MemoryPage::GetAvailableSize() const
{
    return AvailableSize;
}

void* MemoryPage::Allocate(int size, int usingFrame)
{
    if (AvailableSize < size)
    {
        return nullptr;
    }
    else
    {
        auto result = Data[AvailableSize];
        UsingFrame = max(usingFrame, UsingFrame);


    }
}

void* MemoryPage::GetData() const
{
    return Data;
}

ID3D12Resource* MemoryPage::GetResource() const
{
    return Resource.Get();
}

D3D12_GPU_VIRTUAL_ADDRESS MemoryPage::GetGPUVirtualAddress() const
{
    return Resource->GetGPUVirtualAddress();
}