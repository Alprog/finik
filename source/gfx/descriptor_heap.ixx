export module descriptors:heap;

import dx;
import :handle;

export class DescriptorHeap
{
public:
    DescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, unsigned int maxCount);

    ID3D12DescriptorHeap* get() { return heap.Get(); }
    DescriptorHandle getNextHandle();

    inline CD3DX12_CPU_DESCRIPTOR_HANDLE getCpuHandle(int index)
    {
        return {cpuStartHandle, index * handleIncrementSize};
    }

    inline CD3DX12_GPU_DESCRIPTOR_HANDLE getGpuHandle(int index)
    {
        return {gpuStartHandle, index * handleIncrementSize};
    }

private:
    ComPtr<ID3D12DescriptorHeap> heap;

    CD3DX12_CPU_DESCRIPTOR_HANDLE cpuStartHandle;
    CD3DX12_GPU_DESCRIPTOR_HANDLE gpuStartHandle;
    int handleIncrementSize;

    int descriptorCount;
    int maxCount;
};
