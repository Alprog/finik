#pragma once

#include "dx.h"

class RenderSystem;

class UploadBuffer
{
public:
    UploadBuffer(RenderSystem& renderSystem, int size);

    int GetSize() const;
    void* GetData() const;
    ID3D12Resource* GetResource() const;
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const;
   
private:
    int Size;
    ComPtr<ID3D12Resource> Resource;
    void* Data;
};