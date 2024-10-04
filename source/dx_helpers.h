#pragma once

#define FAILED(hr) (((HRESULT)(hr)) < 0)
#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), reinterpret_cast<void**>(ppType)