#pragma once

#include "dx.h"

class RenderSystem;

class GpuProfiler
{
public:
    GpuProfiler(RenderSystem& renderSystem);

    void addStamp(ID3D12GraphicsCommandList& commandList, void* name);

private:
    ComPtr<ID3D12QueryHeap> queryHeap;
    ComPtr<ID3D12Resource> resultBuffer;

    int index = 0;
};