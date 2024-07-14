
#include "constant_buffer.h"
#include "render_system.h"

ConstantBuffer::ConstantBuffer(RenderSystem& renderSystem)
    : version{0}
    , gpuVersion{0}
{
    auto device = renderSystem.get_device();

    auto result = device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(1024 * 64),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&constantBufferResource));

    if (FAILED(result)) throw;

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = constantBufferResource->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = (sizeof(data) + 255) & ~255; // align 256

    descriptorHandle = renderSystem.getSrvCbvHeap()->getNextHandle();
    device->CreateConstantBufferView(&cbvDesc, descriptorHandle.getCPU());

    CD3DX12_RANGE readRange(0, 0);
    result = constantBufferResource->Map(0, &readRange, reinterpret_cast<void**>(&gpuDataBegin));
    if (FAILED(result)) throw;

    update();
}

void ConstantBuffer::update()
{
    if (gpuVersion != version)
    {
        memcpy(gpuDataBegin, &data, sizeof(data));
        gpuVersion = version;
    }
}

