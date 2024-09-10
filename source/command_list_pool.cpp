#include "command_list_pool.h"

#include "command_list.h"

CommandListPool::CommandListPool(RenderSystem& renderSystem)
    : renderSystem{ renderSystem }
{
}

CommandList& CommandListPool::retrieveOne()
{
    if (freeLists.empty())
    {
        auto newList = new CommandList(renderSystem, *this);
        return *newList;
    }

    auto& list = *freeLists.back();
    freeLists.pop_back();
    list.reset();
    return list;
}

void CommandListPool::putBack(CommandList& commandList)
{
    freeLists.push_back(&commandList);
}