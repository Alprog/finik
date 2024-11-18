module;
#include "dx.h"
module texture;

import app;
import descriptor_heap;
import render_system;
import upload_buffer;
import images;

static const uint32 TexturePixelSize = 4;

Texture::Texture(int width, int height)
    : Width{ width }
    , Height{ height }
{
    auto& renderSystem = App::GetInstance().render_system;

    auto device = renderSystem.get_device();
    auto commandList = renderSystem.get_command_list();

    ID3D12CommandAllocator* commandAllocator = nullptr;
    if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)) != S_OK)
        throw;

    auto& commandQueue = renderSystem.get_command_queue();

    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = Width;
    textureDesc.Height = Height;
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
        IID_PPV_ARGS(&InternalResource)) MUST;

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    DescriptorHeap* heap = renderSystem.getSrvCbvHeap();
    descriptorHandle = heap->getNextHandle();
    device->CreateShaderResourceView(InternalResource, &srvDesc, descriptorHandle.getCPU());
}

Texture::Texture(Image& image)
    : Texture(image.width, image.height)
{
    setData(image);
}

Texture::Texture(Path path)
    : Texture(*Images::loadPng(path))
{
}

void Texture::HotReload(Blob& blob)
{

}

void Texture::setData(Image& image)
{
    //image->generateChessboard();

    auto& renderSystem = App::GetInstance().render_system;

    auto device = renderSystem.get_device();
    auto commandList = renderSystem.get_command_list();

    ID3D12CommandAllocator* commandAllocator = nullptr;
    if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)) != S_OK)
        throw;

    auto& commandQueue = renderSystem.get_command_queue();

    const uint64 uploadBufferSize = GetRequiredIntermediateSize(InternalResource, 0, 1);

    UploadBuffer uploadBuffer(renderSystem, uploadBufferSize);
    memcpy(uploadBuffer.GetData(), image.data, uploadBufferSize);

    //D3D12_SUBRESOURCE_DATA textureData = {};
    //textureData.pData = image->data;
    //textureData.RowPitch = image->width * TexturePixelSize;
    //textureData.SlicePitch = textureData.RowPitch * image->height;


    commandList->Reset(commandAllocator, nullptr);
    //UpdateSubresources(commandList, texture.Get(), uploadBuffer.GetResource(), 0, 0, 1, &textureData);

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT srcFootprint;
    uint32 numRows;
    uint64 rowSizeInBytes, totalBytes;
    device->GetCopyableFootprints(&InternalResource->GetDesc(), 0, 1, 0, &srcFootprint, &numRows, &rowSizeInBytes, &totalBytes);

    const CD3DX12_TEXTURE_COPY_LOCATION Src(uploadBuffer.GetResource(), srcFootprint);
    const CD3DX12_TEXTURE_COPY_LOCATION Dst(InternalResource, 0);
    commandList->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);

    commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(InternalResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    commandList->Close();
    ID3D12CommandList* ppCommandLists[] = { commandList };
    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
    commandQueue.Flush();
}