export module resource_storage;

import core;
import gpu_resource;
import descriptor_heap;

export class ResourceStorage
{

private:
    Array<GpuResource*> Resources;

    DescriptorHeap Heap;
};