#include "render_system.h"

#include <SDL.h>
#include <SDL_syswm.h>

#include <d3d12.h>
#include <dxgi1_4.h>

#include "imgui.h"
#include "backends/imgui_impl_dx12.h"
#include "backends/imgui_impl_sdl2.h"

#include <tchar.h>

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif

#include "imgui_internal.h"
#include "pipeline_state.h"

#include "app.h"
#include "desktop_window.h"

class ResultChecker
{
public:
    ResultChecker() = default;

    ResultChecker(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw std::exception();
        }
    }

    void operator|=(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw std::exception();
        }
    }
};

static int const NUM_BACK_BUFFERS = 3;

RenderSystem::RenderSystem()
{
    init();
}

void RenderSystem::init()
{
    enableDebugLayer();
    createDevice();
    setupDebug();
    createCommandQueue();
    createDescriptorHeap();
    createCommandList();
    createRenderContext();
}

void RenderSystem::enableDebugLayer()
{
    ComPtr<ID3D12Debug> debugInterface;
    auto result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface));
    if (SUCCEEDED(result))
    {
        debugInterface->EnableDebugLayer();
    }
}

void RenderSystem::createDevice()
{
    ComPtr<IDXGIFactory4> factory;
    auto result = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(result)) throw;

    ComPtr<IDXGIAdapter1> adapter;
    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory.Get()->EnumAdapters1(adapterIndex, &adapter); adapterIndex++)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        if ((desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0)
        {
            auto result = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr);
            if (SUCCEEDED(result))
            {
                break;
            }
        }
    }

    ComPtr<IDXGIAdapter1> hardwareAdapter;
    hardwareAdapter = adapter.Detach();

    result = D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
    if (FAILED(result)) throw;
}

void RenderSystem::setupDebug()
{
#ifdef DX12_ENABLE_DEBUG_LAYER
    ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(device.As(&pInfoQueue)))
    {
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

        // Suppress whole categories of messages
        //D3D12_MESSAGE_CATEGORY Categories[] = {};

        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        // Suppress individual messages by their ID
        D3D12_MESSAGE_ID DenyIds[] = {
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   // I'm really not sure how to avoid this message.
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
        };

        D3D12_INFO_QUEUE_FILTER NewFilter = {};
        //NewFilter.DenyList.NumCategories = _countof(Categories);
        //NewFilter.DenyList.pCategoryList = Categories;
        NewFilter.DenyList.NumSeverities = _countof(Severities);
        NewFilter.DenyList.pSeverityList = Severities;
        NewFilter.DenyList.NumIDs = _countof(DenyIds);
        NewFilter.DenyList.pIDList = DenyIds;

        auto result = pInfoQueue->PushStorageFilter(&NewFilter);
        if (FAILED(result)) throw;
    }
#endif
}

void RenderSystem::createCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    auto result = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
    if (FAILED(result)) throw;
}

void RenderSystem::createDescriptorHeap()
{
    int count = NUM_BACK_BUFFERS * 2;
    rtvHeap = std::make_unique<DescriptorHeap>(device.Get(), D3D12_DESCRIPTOR_HEAP_TYPE_RTV, count);
    rtvHandle = rtvHeap->getCpuHandle(0);

    dsvHeap = std::make_unique<DescriptorHeap>(device.Get(), D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 2);

    srvCbvHeap = std::make_unique<DescriptorHeap>(device.Get(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 10);
}

void RenderSystem::createCommandList()
{
    ComPtr<ID3D12CommandAllocator> allocator;
    auto result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator));
    if (FAILED(result)) throw;

    result = get_device()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
    if (FAILED(result)) throw;
    
    result = commandList->Close();
    if (FAILED(result)) throw;
}

void RenderSystem::createRenderContext()
{
    renderContext = std::make_unique<RenderContext>(*this, *commandList.Get());
}

void RenderSystem::ImguiInitHelper()
{
    const int NUM_FRAMES_IN_FLIGHT = 3;

    DescriptorHandle handle = srvCbvHeap->getNextHandle();
    ImGui_ImplDX12_Init(device.Get(), NUM_FRAMES_IN_FLIGHT, DXGI_FORMAT_R8G8B8A8_UNORM, srvCbvHeap->get(), handle.getCPU(), handle.getGPU());
}

ID3D12Device* RenderSystem::get_device()
{
    return device.Get();
}

ID3D12CommandQueue* RenderSystem::get_command_queue()
{
    return commandQueue.Get();
}

ID3D12GraphicsCommandList* RenderSystem::get_command_list()
{
    return commandList.Get();
}

DescriptorHeap* RenderSystem::getRtvHeap()
{
    return rtvHeap.get();
}

DescriptorHeap* RenderSystem::getDsvHeap()
{
    return dsvHeap.get();
}

DescriptorHeap* RenderSystem::getSrvCbvHeap()
{
    return srvCbvHeap.get();
}

RenderContext* RenderSystem::getRenderContext()
{
    return renderContext.get();
}