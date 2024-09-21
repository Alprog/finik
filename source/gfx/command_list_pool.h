#pragma once

#include <math.h>
#include "command_list.h"

import std;

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