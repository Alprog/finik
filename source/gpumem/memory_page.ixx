export module memory_page;

import types;
import dx;
import render_system_fwd;
import allocation;

export namespace finik::gpumem
{   
    class MemoryPage
    {
    public:
        MemoryPage(RenderSystem& renderSystem, int size);

        int GetFullSize() const;
        int GetAvailableSize() const;

        Allocation Allocate(int size, int usingFrame);

        byte* GetData() const;
        ID3D12Resource* GetResource() const;
        D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

    private:
        ID3D12Resource* Resource;
        byte* Data;

        int32 FullSize;
        int32 UsedSize;
        int32 UsingFrame;
    };
}