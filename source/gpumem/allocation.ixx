module;
#include "gfx/dx.h"
export module allocation;

export namespace finik::gpumem
{
    void* CpuData;
    D3D12_GPU_VIRTUAL_ADDRESS GpuAddress;
}
