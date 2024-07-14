#pragma once

#include "dx.h"

#include "descriptor_handle.h"

class RenderTarget
{
public:
    ComPtr<ID3D12Resource> resource;
    D3D12_CPU_DESCRIPTOR_HANDLE handle;
};