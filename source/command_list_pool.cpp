#include "command_list_pool.h"

#include "command_list.h"
#include "app.h"

CommandListPool::CommandListPool(RenderSystem& renderSystem)
    : renderSystem{ renderSystem }
{
}

CommandList& CommandListPool::retrieveOne()
{
    auto frameIndex = App::get_instance().getFrameIndex();
    
    if (freeLists.empty())
    {
        return *lists.emplace_back(std::make_unique<CommandList>(renderSystem, *this, frameIndex));
    }

    auto& list = *freeLists.back();
    freeLists.pop_back();
    list.reset(frameIndex);
    return list;
}

void CommandListPool::putBack(CommandList& commandList)
{
    freeLists.push_back(&commandList);
}