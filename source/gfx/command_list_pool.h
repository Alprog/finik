#pragma once

#include <vector>

#include "command_list.h"

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

    std::vector<std::unique_ptr<CommandList>> lists;
    std::vector<CommandList*> freeLists;
};