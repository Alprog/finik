
#pragma once

#include "dx.h"
#include "math/matrix.h"
#include "descriptor_handle.h"
#include "constant_buffer.h"

class DXRenderer;
class RenderSystem;
class UploadBuffer;

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
        Matrix MVP;
    }
    data;

    int version;

    int gpuVersion;
    UINT8* uploadDataBegin;
};
