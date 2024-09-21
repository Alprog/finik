#pragma once

#include "dx.h"

class DescriptorHeap;

struct DescriptorHandle
{
    DescriptorHandle();
    DescriptorHandle(DescriptorHeap* heap, int index);

    CD3DX12_CPU_DESCRIPTOR_HANDLE getCPU();
    CD3DX12_GPU_DESCRIPTOR_HANDLE getGPU();

private:
    DescriptorHeap* heap;
    int index;
};
