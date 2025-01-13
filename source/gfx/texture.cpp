module;
#include "dx.h"
module texture;

import app;
import descriptor_heap;
import render_system;
import upload_buffer;
import images;
import command_list;

static const uint32 TexturePixelSize = 4;

Texture::Texture(AssetPath asset_path)
    : Asset{asset_path}
    , Width{0}
    , Height{0}
{
    auto& renderSystem = App::GetInstance().render_system;
    DescriptorHeap* heap = renderSystem.getSrvCbvHeap();
    descriptorHandle = heap->getNextHandle();
}

int32 Texture::calcMipMapCount()
{
    int32 maxSide = max(Width, Height);
    float count = std::log2(static_cast<float>(maxSide));
    return static_cast<int32>(std::ceil(count));
}

void Texture::resize(int32 width, int32 height)
{
    if (this->Width == width && this->Height == height)
    {
        return;
    }

    this->Width = width;
    this->Height = height;

    if (InternalResource)
    {
        InternalResource->Release();
        InternalResource = nullptr;
    }

    auto& renderSystem = App::GetInstance().render_system;
    auto* device = renderSystem.get_device();

    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = calcMipMapCount();
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Width = width;
    textureDesc.Height = height;
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

    state = D3D12_RESOURCE_STATE_COPY_DEST;

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = textureDesc.MipLevels;

    device->CreateShaderResourceView(InternalResource, &srvDesc, descriptorHandle.getCPU());
}

Texture::Texture(int32 width, int32 height)
    : Texture("")
{
    resize(width, height);
}

Texture::Texture(Image& image)
    : Texture(image.width, image.height)
{
    setData(image);
}

void Texture::hot_reload(ByteBlob& blob)
{
    Image* image = Images::loadPng(blob);
    resize(image->width, image->height);
    setData(*image);
}

void Texture::setData(Image& image)
{
    auto& renderSystem = App::GetInstance().render_system;

    auto device = renderSystem.get_device();
    CommandList& commandList = renderSystem.getFreeCommandList();
    commandList.startRecording();

    //ID3D12CommandAllocator* commandAllocator = nullptr;
    //if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)) != S_OK)
    //    throw;

    //commandList->Reset(commandAllocator, nullptr);
    if (state == D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
    {
        commandList.listImpl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(InternalResource, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST));
    }

    const uint64 uploadBufferSize = GetRequiredIntermediateSize(InternalResource, 0, 1);
    UploadBuffer uploadBuffer(renderSystem, uploadBufferSize);

    if (uploadBufferSize == image.getByteSize())
    {
        memcpy(uploadBuffer.GetData(), image.data, uploadBufferSize);
    }
    else
    {
        D3D12_SUBRESOURCE_DATA textureData = {};
        textureData.pData = image.data;
        textureData.RowPitch = image.width * TexturePixelSize;
        textureData.SlicePitch = textureData.RowPitch * image.height;
        UpdateSubresources(commandList.listImpl.Get(), InternalResource, uploadBuffer.GetResource(), 0, 0, 1, &textureData);
    }

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT srcFootprint;
    uint32 numRows;
    uint64 rowSizeInBytes, totalBytes;
    device->GetCopyableFootprints(&InternalResource->GetDesc(), 0, 1, 0, &srcFootprint, &numRows, &rowSizeInBytes, &totalBytes);

    const CD3DX12_TEXTURE_COPY_LOCATION Src(uploadBuffer.GetResource(), srcFootprint);
    const CD3DX12_TEXTURE_COPY_LOCATION Dst(InternalResource, 0);
    commandList.listImpl->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);

    commandList.listImpl->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(InternalResource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    commandList.endRecording();

    auto& commandQueue = renderSystem.get_command_queue();
    commandQueue.execute(commandList);
    commandQueue.Flush();

    state = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
}