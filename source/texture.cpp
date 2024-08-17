#include "texture.h"

#include "images.h"
#include "descriptor_heap.h"
#include "dx.h"
#include "app.h"
#include "render_system.h"

static const UINT TexturePixelSize = 4;

Texture::Texture(std::string filePath)
{
    auto image = Images::loadPng(filePath);
    //image->generateChessboard();

    auto& renderSystem = App::get_instance().render_system;

    auto device = renderSystem.get_device();
    auto commandList = renderSystem.get_command_list();

    ID3D12CommandAllocator* commandAllocator = nullptr;
    if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)) != S_OK)
        throw;

    auto& commandQueue = renderSystem.get_command_queue();

    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = image->width;
    textureDesc.Height = image->height;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

    device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&texture)) MUST;

    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(texture.Get(), 0, 1);

    ComPtr<ID3D12Resource> textureUploadHeap;

    device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&textureUploadHeap)) MUST;

    D3D12_SUBRESOURCE_DATA textureData = {};
    textureData.pData = image->data;
    textureData.RowPitch = image->width * TexturePixelSize;
    textureData.SlicePitch = textureData.RowPitch * image->height;

    commandList->Reset(commandAllocator, nullptr);
    UpdateSubresources(commandList, texture.Get(), textureUploadHeap.Get(), 0, 0, 1, &textureData);
    commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    commandList->Close();
    ID3D12CommandList* ppCommandLists[] = { commandList };
    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    descriptorHandle = renderSystem.getSrvCbvHeap()->getNextHandle();
    device->CreateShaderResourceView(texture.Get(), &srvDesc, descriptorHandle.getCPU());

    commandQueue.Flush();

    delete image;
}