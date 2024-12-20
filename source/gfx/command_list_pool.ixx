export module command_list_pool;

import core;
import render_system_fwd;
import command_list;

export class CommandListPool
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