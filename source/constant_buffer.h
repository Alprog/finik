
#pragma once

#include "dx.h"
#include "descriptor_handle.h"
#include "constant_buffer.h"

class DXRenderer;
class RenderSystem;
class UploadBuffer;

import math;

class ConstantBuffer
{
public:
    ConstantBuffer() = default;
    ConstantBuffer(RenderSystem& renderSystem);
    ~ConstantBuffer();

    void update();

    UploadBuffer* uploadBuffer;
    DescriptorHandle descriptorHandle;

    struct
    {
        Matrix ViewProjection;
    }
    data;

    int version;

    int gpuVersion;
    UINT8* uploadDataBegin;
};
