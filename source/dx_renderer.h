
#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <unordered_map>

using namespace Microsoft::WRL;

class Texture;
class Shader;
class ConstantBuffer;
class DXDescriptorHeap;

struct RenderCommand
{

};

class DXRenderer
{
public:
    DXRenderer();
    virtual ~DXRenderer();

    void init();
    void enableDebugLayer();
    void createDevice();
    void createCommandQueue();
    void createDescriptorHeap();
    void createCommandAllocator();
    void createCommandListAndFence();
    void waitForPreviousFrame();

    void populateCommandList(std::vector<RenderCommand> commands);

    void initSwapChain(HWND hwnd, int width, int height);
    ComPtr<IDXGISwapChain3> createSwapChain(HWND hwnd, int width, int height);
    void render();

    inline ID3D12Device* getDevice() { return device.Get(); }
    inline ID3D12GraphicsCommandList* getCommandList() { return commandList.Get(); }
    inline DXDescriptorHeap* getSrvCbvHeap() { return srvCbvHeap; }

    inline ID3D12CommandAllocator* getCommandAllocator() { return commandAllocator.Get(); }
    inline ID3D12CommandQueue* getCommandQueue() { return commandQueue.Get(); }

private:
    ComPtr<ID3D12Device> device;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<IDXGISwapChain3> swapChain;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12DescriptorHeap> dsvHeap;
    DXDescriptorHeap* srvCbvHeap;
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12Resource> renderTargets[2];
    ComPtr<ID3D12Resource> depthStencil;
    UINT rtvDescriptorSize;

    ComPtr<ID3D12GraphicsCommandList> commandList;
    UINT frameIndex;
    HANDLE fenceEvent;
    ComPtr<ID3D12Fence> fence;
    UINT64 fenceValue;
};
