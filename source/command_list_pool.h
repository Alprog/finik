#pragma once

#include <vector>

class CommandList;
class RenderSystem;

class CommandListPool
{
    friend class CommandList;

public:
    explicit CommandListPool(RenderSystem& renderSystem);

    CommandList& retrieveOne();
    void putBack(CommandList& commandList);

private:
    RenderSystem& renderSystem;
    
    std::vector<CommandList*> freeLists;
};