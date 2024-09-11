#pragma once

#include "dx.h"

class RenderSystem;
class CommandListPool;

class CommandList
{
public:
    explicit CommandList(RenderSystem& renderSystem, CommandListPool& pool, int frameIndex);
    void reset(int frameIndex);
    void returnToPool();

    int getFrameIndex() const;

    ComPtr<ID3D12GraphicsCommandList> listImpl;
    ComPtr<ID3D12CommandAllocator> commandAllocator;

private:
    RenderSystem& renderSystem;
    CommandListPool& pool;
    int frameIndex;
};