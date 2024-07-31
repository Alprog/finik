#pragma once

#include "dx.h"

#include "descriptor_handle.h"

class RenderTarget
{
public:
    ComPtr<ID3D12Resource> resource;    // render target texture
    D3D12_CPU_DESCRIPTOR_HANDLE handle;
};