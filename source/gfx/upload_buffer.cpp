module UploadBuffer;

import render_system;

UploadBuffer::UploadBuffer(RenderSystem& renderSystem, int size)
    : Size { size }
{
    auto device = renderSystem.get_device();

    auto result = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
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

int UploadBuffer::GetSize() const
{
    return Size;
}

void* UploadBuffer::GetData() const
{
    return Data;
}

ID3D12Resource* UploadBuffer::GetResource() const
{
    return Resource.Get();
}

D3D12_GPU_VIRTUAL_ADDRESS UploadBuffer::GetGPUVirtualAddress() const
{
    return Resource->GetGPUVirtualAddress();
}