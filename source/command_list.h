#pragma once

#include "dx.h"

class RenderSystem;
class CommandListPool;

class CommandList
{
public:
    explicit CommandList(RenderSystem& renderSystem, CommandListPool& pool);
    void reset();

    void returnToPool();

    ComPtr<ID3D12GraphicsCommandList> listImpl;
    ComPtr<ID3D12CommandAllocator> commandAllocator;

private:
    RenderSystem& renderSystem;
    CommandListPool& pool;
};