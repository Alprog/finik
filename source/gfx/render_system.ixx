module;
class Window;
export module render_system;

import render_system_fwd;

import core;
import dx;
import command_queue;
import command_list_pool;
import render_lane;
import render_context;
import gpu_profiler;
import myptr;
import oneshot_allocator;
import root_signature;

export class RenderSystem
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
    RootSignature& getRootSignature();

    CommandList& getFreeCommandList();
    finik::gpumem::OneshotAllocator& getOneshotAllocator();

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
    void createRootSignature();
    
    CommandQueue* commandQueue = nullptr;
    MyPtr<ID3D12CommandAllocator> commandAllocators[3];
    MyPtr<ID3D12GraphicsCommandList> commandList;

    std::unique_ptr<RootSignature> rootSignature;

    GpuProfiler* gpuProfiler = nullptr;

    std::unique_ptr<RenderContext> renderContext;

    std::unique_ptr<DescriptorHeap> rtvHeap; // Render Target View
    std::unique_ptr<DescriptorHeap> dsvHeap; // Depth Stencil View
    std::unique_ptr<DescriptorHeap> srvCbvHeap;

    MyPtr<ID3D12Device> device;

    std::shared_ptr<PipelineState> pipelineState;

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

    std::unique_ptr<CommandListPool> commandListPool;
    std::unique_ptr<finik::gpumem::OneshotAllocator> oneshotAllocator;

public:
    Array<std::shared_ptr<RenderLane>> lanes;
};