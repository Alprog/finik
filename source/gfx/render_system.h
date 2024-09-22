#pragma once

#include "dx.h"
#include <dxgi1_4.h>

#include "descriptor_heap.h"
#include "render_context.h"
#include "render_lane.h"
#include "command_queue.h"
#include "command_list_pool.h"
#include "../gpumem/oneshot_allocator.h"

class Window;
class PipelineState;
struct FrameContext;
class RenderContext;
class GpuProfiler;

class RenderSystem
{
    friend class App;

    RenderSystem();

public:
    void init();

    ID3D12Device* get_device();
    CommandQueue& get_command_queue();
    ID3D12GraphicsCommandList* get_command_list();
    DescriptorHeap* getRtvHeap();
    DescriptorHeap* getDsvHeap();
    DescriptorHeap* getSrvCbvHeap();
    RenderContext* getRenderContext();
    GpuProfiler* getProfiler();

    CommandList& getFreeCommandList();

    void ImguiInitHelper();

    void scheduleQueryResolving();

private:
    void enableDebugLayer();
    void createDevice();
    void setupDebug();
    void createCommandQueue();
    void createDescriptorHeap();
    void createCommandListPool();
    void createCommandAllocators();
    void createOneshotAllocator();
    void createCommandList();   
    void createRenderContext();
    void createProfiler();
    
    ComPtr<ID3D12Device> device = nullptr;
    CommandQueue* commandQueue = nullptr;
    ComPtr<ID3D12CommandAllocator> commandAllocators[3];
    ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;

    GpuProfiler* gpuProfiler = nullptr;

    std::unique_ptr<RenderContext> renderContext;

    std::unique_ptr<DescriptorHeap> rtvHeap; // Render Target View
    std::unique_ptr<DescriptorHeap> dsvHeap; // Depth Stencil View
    std::unique_ptr<DescriptorHeap> srvCbvHeap;

    std::shared_ptr<PipelineState> pipelineState;

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

    std::unique_ptr<CommandListPool> commandListPool;
    std::unique_ptr<finik::gpumem::OneshotAllocator> oneshotAllocator;

public:
    std::vector<std::shared_ptr<RenderLane>> lanes;
};