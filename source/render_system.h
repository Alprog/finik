#pragma once

class Window;
struct FrameContext;

#include "dx.h"
#include <dxgi1_4.h>

#include "descriptor_heap.h"

class RenderSystem
{
public:
    friend class App;

    RenderSystem();

    void init();

    ID3D12Device* get_device();
    ID3D12CommandQueue* get_command_queue();
    ID3D12GraphicsCommandList* get_command_list();
    DescriptorHeap* getRtvDescHeap();
    DescriptorHeap* getDstDescHeap();
    DescriptorHeap* getSrvDescHeap();
    void ImguiInitHelper();

private:
    void enableDebugLayer();
    void createDevice();
    void setupDebug();
    void createCommandQueue();
    void createDescriptorHeap();
    void createCommandList();
    
    ComPtr<ID3D12Device> device = nullptr;
    ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
    ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;

    std::unique_ptr<DescriptorHeap> rtvDescHeap; // Render Target View
    std::unique_ptr<DescriptorHeap> dsvDescHeap; // Depth Stencil View
    std::unique_ptr<DescriptorHeap> srvDescHeap;


    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
};