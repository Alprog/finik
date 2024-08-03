#pragma once

class Window;
class PipelineState;
struct FrameContext;
class RenderContext;

#include "dx.h"
#include <dxgi1_4.h>

#include "descriptor_heap.h"
#include "render_context.h"
#include "render_lane.h"

class RenderSystem
{
    friend class App;

    RenderSystem();

public:
    void init();

    ID3D12Device* get_device();
    ID3D12CommandQueue* get_command_queue();
    ID3D12GraphicsCommandList* get_command_list();
    DescriptorHeap* getRtvHeap();
    DescriptorHeap* getDsvHeap();
    DescriptorHeap* getSrvCbvHeap();
    RenderContext* getRenderContext();

    void ImguiInitHelper();

private:
    void enableDebugLayer();
    void createDevice();
    void setupDebug();
    void createCommandQueue();
    void createDescriptorHeap();
    void createCommandList();
    void createRenderContext();
    
    ComPtr<ID3D12Device> device = nullptr;
    ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
    ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;

    std::unique_ptr<RenderContext> renderContext;

    std::unique_ptr<DescriptorHeap> rtvHeap; // Render Target View
    std::unique_ptr<DescriptorHeap> dsvHeap; // Depth Stencil View
    std::unique_ptr<DescriptorHeap> srvCbvHeap;

    std::shared_ptr<PipelineState> pipelineState;

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

public:
    std::vector<std::shared_ptr<RenderLane>> lanes;
};