#pragma once

#include "memory_page.h"

class RenderSystem;

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