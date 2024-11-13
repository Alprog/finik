module;
#include "asserts.h"
module resource;

Resource::~Resource()
{
    int32 Result = InternalResource->Release();
    ASSERT(Result == 0);
    InternalResource = nullptr;
}