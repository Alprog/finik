module descriptors:handle;

import :heap;

DescriptorHandle::DescriptorHandle()
    : heap {nullptr}
    , index {0}
{
}

DescriptorHandle::DescriptorHandle(DescriptorHeap* heap, int index)
    : heap {heap}
    , index {index}
{
}

CD3DX12_CPU_DESCRIPTOR_HANDLE DescriptorHandle::getCPU()
{
    return heap->getCpuHandle(index);
}

CD3DX12_GPU_DESCRIPTOR_HANDLE DescriptorHandle::getGPU()
{
    return heap->getGpuHandle(index);
}
