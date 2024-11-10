module oneshot_allocator;

import render_system;
import std;

using namespace finik::gpumem;

OneshotAllocator::OneshotAllocator(RenderSystem& renderSystem)
    : renderSystem{ renderSystem }
{
}

Allocation OneshotAllocator::Allocate(const int size, const int frame)
{
    constexpr int32 alignmentMask = 0xFF;
    const int32 allignedSize = (size + alignmentMask) & ~alignmentMask;

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