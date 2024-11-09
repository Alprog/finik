export module allocation;

import dx;
import types;

export namespace finik::gpumem
{
    struct Allocation
    {
        byte* CpuData;
        D3D12_GPU_VIRTUAL_ADDRESS GpuAddress;
    };
}
