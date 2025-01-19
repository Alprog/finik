module;
#include "asserts.h"
#include "gfx/dx.h"
module gpu_resource;

import command_list;
import app;

GpuResource::~GpuResource()
{
    int32 Result = InternalResource->Release();
    ASSERT(Result == 0);
    InternalResource = nullptr;
}

void GpuResource::reinit(D3D12_RESOURCE_DESC desc, D3D12_RESOURCE_STATES initialState, const D3D12_CLEAR_VALUE* clearValue)
{
    if (InternalResource)
    {
        InternalResource->Release();
        InternalResource = nullptr;
    }

    auto device = App::GetInstance().render_system.get_device();
    device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &desc,
        initialState,
        clearValue,
        IID_PPV_ARGS(&InternalResource)) MUST;

    state = initialState;
}

void GpuResource::transition_to(D3D12_RESOURCE_STATES newState, CommandList& list)
{
    if (state != newState)
    {
        list.listImpl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(InternalResource, state, newState));
        state = newState;
    }
}