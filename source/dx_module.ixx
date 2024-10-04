module;
//#include "gfx/dx.h"
//#include <dxgi1_4.h>
export module dx;
//
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
//
//// d3dx12
//export CD3DX12_CPU_DESCRIPTOR_HANDLE;
//export CD3DX12_GPU_DESCRIPTOR_HANDLE;
//export CD3DX12_HEAP_PROPERTIES;
//
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
