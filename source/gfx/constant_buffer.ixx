export module constant_buffer;

import core;
import descriptor_handle;
import render_system_fwd;
import root_signature_params;

export class GpuDataBuffer
{
public:
    GpuDataBuffer(int32 size, RenderSystem& renderSystem);
    virtual ~GpuDataBuffer();

    UploadBuffer* uploadBuffer;
    DescriptorHandle descriptorHandle;
    uint8* data;
    int32 size;
};

export template <typename T>
class GpuBuffer : public GpuDataBuffer
{
public:
    GpuBuffer(RenderSystem& renderSystem)
        : GpuDataBuffer(sizeof(T), renderSystem)
    {
    }

    T* operator->()
    {
        return reinterpret_cast<T*>(data);
    }
};

export using GpuFrameConstantBuffer = GpuBuffer<FrameConstantBuffer>;