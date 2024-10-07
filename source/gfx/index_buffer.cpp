module;
#include "dx.h"
module index_buffer;

import app;
import render_system;

void IndexBuffer::Load()
{
    auto device = App::get_instance().render_system.get_device();

    const UINT indexBufferSize = indices.size() * sizeof(uint32_t);

    auto result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBufferResource));
    if (FAILED(result)) throw;

    UINT8* data;
    CD3DX12_RANGE readRange(0, 0);

    result = indexBufferResource->Map(0, &readRange, reinterpret_cast<void**>(&data));
    if (FAILED(result)) throw;
    std::memcpy(data, &indices[0], indexBufferSize);
    indexBufferResource->Unmap(0, nullptr);

    indexBufferView.BufferLocation = indexBufferResource->GetGPUVirtualAddress();
    indexBufferView.Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
    indexBufferView.SizeInBytes = indexBufferSize;
}
