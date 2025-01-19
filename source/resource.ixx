export module gpu_resource;

import core;
import dx;
import render_system_fwd;

export class GpuResource
{
public:
    GpuResource() = default;
    virtual ~GpuResource();

    void reinit(D3D12_RESOURCE_DESC desc, D3D12_RESOURCE_STATES initialState, const D3D12_CLEAR_VALUE* clearValue = nullptr);

    ID3D12Resource* getInternal() const
    {
        return InternalResource;
    }

    void transition_to(D3D12_RESOURCE_STATES newState, CommandList& list);

public:
    ID3D12Resource* InternalResource = nullptr;
    D3D12_RESOURCE_STATES state;
};