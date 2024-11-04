module;
#include "dx.h"
module constant_buffer;

import render_system;
import upload_buffer;
import descriptor_heap;

ConstantBuffer::ConstantBuffer(RenderSystem& renderSystem)
    : version{0}
    , gpuVersion{0}
{
    uploadBuffer = new UploadBuffer(renderSystem, 1024 * 64);

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = uploadBuffer->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = (sizeof(data) + 255) & ~255; // align 256

    uploadDataBegin = (uint8*)uploadBuffer->GetData();

    descriptorHandle = renderSystem.getSrvCbvHeap()->getNextHandle();
    renderSystem.get_device()->CreateConstantBufferView(&cbvDesc, descriptorHandle.getCPU());

    update();
}

void ConstantBuffer::update()
{
    if (gpuVersion != version)
    {
        memcpy(uploadDataBegin, &data, sizeof(data));
        gpuVersion = version;
    }
}

