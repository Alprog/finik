export module resource_storage;

import core;
import gpu_resource;
import descriptor_heap;

export class ResourceStorage
{

private:
    std::vector<GpuResource*> Resources;

    DescriptorHeap Heap;
};