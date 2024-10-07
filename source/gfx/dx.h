#pragma once

// wrl asserts include somewhere in deep <crtdbg.h>
// and then <vcruntime_new.h> which define std::align_val_t and conflict with import std
// disable wrl asserts instead
#define __WRL_ASSERT__(cond)

#include <d3d12.h>
#include <d3dx12.h>

#include <dxgi1_4.h>

#include <wrl/client.h>

#define MUST < 0 ? throw : 0

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

//#define FAILED(hr) (((HRESULT)(hr)) < 0)
//#define D3D12_FLOAT32_MAX	( 3.402823466e+38f )
//#define	D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES	( 0xffffffff )
//#define DXGI_CREATE_FACTORY_DEBUG 0x1
//#define DXGI_STATUS_OCCLUDED ((HRESULT)0x087A0001L)
//#define S_OK                                   ((HRESULT)0L)
//#define S_FALSE                                ((HRESULT)1L)