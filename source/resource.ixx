export module gpu_resource;

import core;
import dx;
import render_system_fwd;

export class GpuResource
{
public:
    GpuResource() = default;

    virtual ~GpuResource();

    ID3D12Resource* getInternal() const
    {
        return InternalResource;
    }

    void transition(CommandList& list, D3D12_RESOURCE_STATES dstState);

public:
    ID3D12Resource* InternalResource = nullptr;
    D3D12_RESOURCE_STATES state;
};