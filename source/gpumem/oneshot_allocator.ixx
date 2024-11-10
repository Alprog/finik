export module oneshot_allocator;

import std;
import memory_page;
import render_system_fwd;
import allocation;

export namespace finik::gpumem
{
    class OneshotAllocator
    {
    public:
        explicit OneshotAllocator(RenderSystem& renderSystem);

        RawAllocation Allocate(int size, int frame);

        template <typename T>
        Allocation<T> Allocate(int usingFrame)
        {
            return Allocation<T>(Allocate(sizeof(T), usingFrame));
        }

    private:
        MemoryPage& CreateNewPage();

        RenderSystem& renderSystem;

        std::vector<MemoryPage> pages;
    };
} 