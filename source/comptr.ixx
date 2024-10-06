module;
#define __WRL_ASSERT__(cond)
#include <wrl/client.h>
export module comptr;

export Microsoft::WRL::ComPtr;

export template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;