#pragma once

class Window;
struct FrameContext;

#include <d3d12.h>
#include <dxgi1_4.h>

class ID3D12CommandQueue;
class ID3D12Device;

class RenderSystem
{
public:
    friend class App;

    RenderSystem();

    bool CreateDeviceD3D();
    void CleanupDeviceD3D();

    ID3D12Device* get_device();
    ID3D12CommandQueue* get_command_queue();
    ID3D12GraphicsCommandList* get_command_list();
    ID3D12DescriptorHeap*& get_srv_heap();

    D3D12_CPU_DESCRIPTOR_HANDLE get_next_rtv_handle();

    void ImguiInitHelper();
};