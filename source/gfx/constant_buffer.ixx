export module constant_buffer;

import descriptor_handle;
import render_system_fwd;

import types;
import math;
import root_signature_params;

export class ConstantBuffer
{
public:
    ConstantBuffer() = default;
    ConstantBuffer(RenderSystem& renderSystem);
    ~ConstantBuffer() = default;

    void update();

    UploadBuffer* uploadBuffer;
    DescriptorHandle descriptorHandle;

    FrameConstantBuffer data;

    int version;

    int gpuVersion;
    uint8* uploadDataBegin;
};
