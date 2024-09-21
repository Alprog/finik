#pragma once

#include "dx.h"
#include "fence.h"
import std.compat;

class RenderSystem;
class CommandList;

class CommandQueue
{
public:
    CommandQueue(RenderSystem& renderSystem);

    void execute(CommandList& commandList);
    void freeCompletedLists();

    ID3D12CommandQueue* operator->();
    
    void Flush();

    ComPtr<ID3D12CommandQueue> queueImpl;
    std::unique_ptr<Fence> fence;

    std::unique_ptr<Fence> frameFence;

    std::queue<CommandList*> executionQueue;
};