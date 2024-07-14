
#pragma once

#include "dx.h"
#include "math/matrix.h"
#include "descriptor_handle.h"
#include "constant_buffer.h"

class DXRenderer;
class RenderSystem;

class ConstantBuffer
{
public:
    ConstantBuffer(RenderSystem& renderSystem);
    void update();

    ComPtr<ID3D12Resource> constantBufferResource;
    DescriptorHandle descriptorHandle;

    struct
    {
        Matrix MVP;
    }
    data;

    int version;

    int gpuVersion;
    UINT8* gpuDataBegin;
};
