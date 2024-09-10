#pragma once

#include "dx.h"
#include "fence.h"
#include <queue>

class RenderSystem;
class CommandList;

class CommandQueue
{
public:
    CommandQueue(RenderSystem& renderSystem);

    void execute(CommandList& commandList);

    ID3D12CommandQueue* operator->();
    
    void Flush();

    ComPtr<ID3D12CommandQueue> queueImpl;
    std::unique_ptr<Fence> fence;

    std::queue<CommandList*> executionQueue;
};