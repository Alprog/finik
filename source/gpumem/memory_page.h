#pragma once

#include "../gfx/dx.h"

class RenderSystem;

namespace finik::gpumem
{   
    class MemoryPage
    {
    public:
        MemoryPage(RenderSystem& renderSystem, int size);

        int GetFullSize() const;
        int GetAvailableSize() const;

        void* Allocate(int size, int usingFrame);

        void* GetData() const;
        ID3D12Resource* GetResource() const;
        D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;

    private:
        int FullSize;
        int AvailableSize;
        int UsingFrame;

        ComPtr<ID3D12Resource> Resource;
        char* Data;
        char* AvailableData;
    };
}