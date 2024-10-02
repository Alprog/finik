module;
#include "gfx/dx.h"
#include <dxgi1_4.h>
export module dx;

export class ID3D12Resource;
export class ID3D12CommandQueue;
export class ID3D12DescriptorHeap;
export class ID3D12Device;
export enum D3D12_DESCRIPTOR_HEAP_TYPE;

export struct D3D12_VERTEX_BUFFER_VIEW;
export typedef UINT64 D3D12_GPU_VIRTUAL_ADDRESS;

// d3dx12
export struct CD3DX12_CPU_DESCRIPTOR_HANDLE;
export struct CD3DX12_GPU_DESCRIPTOR_HANDLE;

// ComPtr
namespace Microsoft::WRL
{
    export template<typename T> class ComPtr;
}

export template<typename T> class ComPtr : public Microsoft::WRL::ComPtr<T>
{
public:
    T* operator->() const throw()
    {
        return Microsoft::WRL::ComPtr<T>::ptr_;
    }
};