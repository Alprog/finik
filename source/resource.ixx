export module gpu_resource;

import core;
import dx;

export class GpuResource
{
public:
    virtual ~GpuResource();

protected:
    ID3D12Resource* InternalResource;
};