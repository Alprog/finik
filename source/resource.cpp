module;
#include "asserts.h"
module gpu_resource;

GpuResource::~GpuResource()
{
    int32 Result = InternalResource->Release();
    ASSERT(Result == 0);
    InternalResource = nullptr;
}