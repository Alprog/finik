export module oneshot_allocator;

import std;
import memory_page;
import render_system_fwd;
import allocation;
import types;

export namespace finik::gpumem
{
    class OneshotAllocator
    {
    public:
        explicit OneshotAllocator(RenderSystem& renderSystem);
        
        RawAllocation Allocate(int size, int frame);

        template <typename T>
        Allocation<T> Allocate()
        {
            const int32 frame = GetCurrentFrame();
            return Allocation<T>(Allocate(sizeof(T), frame));
        }

        void FreePages();

    private:
        int32 GetCurrentFrame();
        
        MemoryPage& CreateNewPage();

        RenderSystem& renderSystem;

        std::vector<MemoryPage> pages;
    };
} 