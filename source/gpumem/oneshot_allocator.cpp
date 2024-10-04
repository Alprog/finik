#include "oneshot_allocator.h"

import render_system;

import std;

using namespace finik::gpumem;

OneshotAllocator::OneshotAllocator(RenderSystem& renderSystem)
    : renderSystem{ renderSystem }
{
}

void* OneshotAllocator::Allocate(const int size, const int frame)
{
    auto allignedSize = size;

    //assert(allignedSize < 4096);

    for (auto& page : pages)
    {
        if (page.GetAvailableSize() >= allignedSize)
        {
            return page.Allocate(allignedSize, frame);
        }
    }


    return CreateNewPage().Allocate(allignedSize, frame);
}

MemoryPage& OneshotAllocator::CreateNewPage()
{
    return pages.emplace_back(renderSystem, 4096);
}