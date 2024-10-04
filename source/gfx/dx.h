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