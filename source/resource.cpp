module;
#include "asserts.h"
module gpu_resource;

import command_list;

GpuResource::~GpuResource()
{
    int32 Result = InternalResource->Release();
    ASSERT(Result == 0);
    InternalResource = nullptr;
}

void GpuResource::transition(CommandList& list, D3D12_RESOURCE_STATES dstState)
{
    if (state != dstState)
    {
        list.listImpl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(InternalResource, state, dstState));
        state = dstState;
    }
}