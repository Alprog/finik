export module constant_buffer;

import descriptor_handle;
import render_system_fwd;

import types;
import math;

struct FrameConstantBuffer
{
    Matrix ViewProjection;
};

export class ConstantBuffer
{
public:
    ConstantBuffer() = default;
    ConstantBuffer(RenderSystem& renderSystem);
    ~ConstantBuffer() = default;

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
    uint8* uploadDataBegin;
};
