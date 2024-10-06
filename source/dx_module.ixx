module;
#define __WRL_ASSERT__(cond)
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_4.h>
export module dx;

//export ID3D12Resource;
//export ID3D12CommandQueue;
//export ID3D12DescriptorHeap;
//export ID3D12Device;
//export ID3D12Fence;
//export ID3D12GraphicsCommandList;
//export ID3D12CommandAllocator;
//export IDXGISwapChain3;
//export ID3D12PipelineState;
//export ID3D12RootSignature;
//export ID3D12QueryHeap;
//export ID3DBlob;
//
//export D3D12_DESCRIPTOR_HEAP_TYPE;
//export D3D12_INDEX_BUFFER_VIEW;
//export D3D12_VERTEX_BUFFER_VIEW;
//export D3D12_GPU_VIRTUAL_ADDRESS;
//export D3D12_CPU_DESCRIPTOR_HANDLE;
//export D3D12_RECT;
//export D3D12_VIEWPORT;
//export D3D12_COMMAND_QUEUE_DESC;
//export D3D12_COMMAND_LIST_TYPE;
//export D3D12_RESOURCE_BARRIER;
//export D3D12_CONSTANT_BUFFER_VIEW_DESC;
//export D3D12_DESCRIPTOR_HEAP_DESC;
//export D3D12_QUERY_HEAP_DESC;
//export D3D12_INPUT_CLASSIFICATION;
//export D3D12_FILTER;
//export D3D12_TEXTURE_ADDRESS_MODE;
//export D3D12_COMPARISON_FUNC;
//export D3D12_STATIC_SAMPLER_DESC;
//export D3D_ROOT_SIGNATURE_VERSION;
//export D3D12_INPUT_ELEMENT_DESC;
//export D3D12_RESOURCE_DIMENSION;
//export D3D12_CLEAR_VALUE;
//
//// d3dx12
//export CD3DX12_CPU_DESCRIPTOR_HANDLE;
//export CD3DX12_GPU_DESCRIPTOR_HANDLE;
//export CD3DX12_HEAP_PROPERTIES;
//export CD3DX12_DESCRIPTOR_RANGE;
//export CD3DX12_RESOURCE_BARRIER;
//export CD3DX12_RANGE;
//export CD3DX12_RESOURCE_DESC;
//export CD3DX12_ROOT_PARAMETER;
//export CD3DX12_DEPTH_STENCIL_DESC;
//export CD3DX12_BLEND_DESC;
//export CD3DX12_RASTERIZER_DESC;
//export CD3DX12_ROOT_SIGNATURE_DESC;
//export CD3DX12_SHADER_BYTECODE;

//export DXGI_FORMAT;

//export HANDLE;
//
//// ComPtr
//namespace Microsoft::WRL
//{
//    export template<typename T> class ComPtr;
//}
//
//export template<typename T> class ComPtr : public Microsoft::WRL::ComPtr<T>
//{
//public:
//    T* operator->() const throw()
//    {
//        return ComPtr<T>::ptr_;
//    }
//};
//
//export template<typename T> _Post_equal_to_(pp) _Post_satisfies_(return == pp) void** IID_PPV_ARGS_Helper(T * *pp);
