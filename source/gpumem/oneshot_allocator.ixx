export module oneshot_allocator;

import std;
import memory_page;
import render_system_fwd;

namespace finik::gpumem
{
    class OneshotAllocator
    {
    public:
        explicit OneshotAllocator(RenderSystem& renderSystem);

        void* Allocate(int size, int frame);

    private:
        MemoryPage& CreateNewPage();

        RenderSystem& renderSystem;

        std::vector<MemoryPage> pages;
    };
} 