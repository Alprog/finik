export module mipmap_generator;

import core;

import dx;

export class MipMapGenerator : public Singleton<MipMapGenerator>
{
public:
    MipMapGenerator();

    MyPtr<ID3D12PipelineState> pso;
};

//
//class GenerateMipsResources
//{
//public:
//    enum RootParameterIndex
//    {
//        Constants,
//        SourceTexture,
//        TargetTexture,
//        RootParameterCount
//    };
//
//#pragma pack(push, 4)
//    struct ConstantData
//    {
//        XMFLOAT2 InvOutTexelSize;
//        uint32_t SrcMipIndex;
//    };
//#pragma pack(pop)
//
//    static constexpr uint32_t Num32BitConstants = static_cast<uint32_t>(sizeof(ConstantData) / sizeof(uint32_t));
//    static constexpr uint32_t ThreadGroupSize = 8;
//
//    ComPtr<ID3D12RootSignature> rootSignature;
//    ComPtr<ID3D12PipelineState> generateMipsPSO;
//
//    GenerateMipsResources(
//        _In_ ID3D12Device* device)
//    {
//        rootSignature = CreateGenMipsRootSignature(device);
//        generateMipsPSO = CreateGenMipsPipelineState(device, rootSignature.Get(), GenerateMips_main, sizeof(GenerateMips_main));
//    }
//
//    GenerateMipsResources(const GenerateMipsResources&) = delete;
//    GenerateMipsResources& operator=(const GenerateMipsResources&) = delete;
//
//    GenerateMipsResources(GenerateMipsResources&&) = default;
//    GenerateMipsResources& operator=(GenerateMipsResources&&) = default;
//
//private:

//
//    static ComPtr<ID3D12PipelineState> CreateGenMipsPipelineState(
//        _In_ ID3D12Device* device,
//        _In_ ID3D12RootSignature* rootSignature,
//        _In_reads_(bytecodeSize) const uint8_t* bytecode,
//        _In_ size_t bytecodeSize)
//    {
//        D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
//        desc.CS.BytecodeLength = bytecodeSize;
//        desc.CS.pShaderBytecode = bytecode;
//        desc.pRootSignature = rootSignature;
//
//        ComPtr<ID3D12PipelineState> pso;
//        ThrowIfFailed(device->CreateComputePipelineState(&desc, IID_GRAPHICS_PPV_ARGS(pso.GetAddressOf())));
//
//        SetDebugObjectName(pso.Get(), L"GenerateMips PSO");
//
//        return pso;
//    }
//};
//
//void GenerateMips_UnorderedAccessPath(
//    _In_ ID3D12Resource* resource)
//{
//#if defined(_MSC_VER) || !defined(_WIN32)
//    const auto desc = resource->GetDesc();
//#else
//    D3D12_RESOURCE_DESC tmpDesc;
//    const auto& desc = *resource->GetDesc(&tmpDesc);
//#endif
//    //assert(!FormatIsBGR(desc.Format) && !FormatIsSRGB(desc.Format));
//
//    const CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
//
//    //assert(mCommandType != D3D12_COMMAND_LIST_TYPE_COPY);
//    const D3D12_RESOURCE_STATES originalState = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
//
//    // Create a staging resource if we have to
//    MyPtr<ID3D12Resource> staging;
//    if ((desc.Flags & D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS) == 0)
//    {
//        D3D12_RESOURCE_DESC stagingDesc = desc;
//        stagingDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
//        stagingDesc.Format = ConvertSRVtoResourceFormat(desc.Format);
//
//        ThrowIfFailed(mDevice->CreateCommittedResource(
//            &defaultHeapProperties,
//            D3D12_HEAP_FLAG_NONE,
//            &stagingDesc,
//            D3D12_RESOURCE_STATE_COPY_DEST,
//            nullptr,
//            IID_GRAPHICS_PPV_ARGS(staging.GetAddressOf())));
//
//        // Copy the top mip of resource to staging
//        TransitionResource(mList.Get(), resource, originalState, D3D12_RESOURCE_STATE_COPY_SOURCE);
//
//        const CD3DX12_TEXTURE_COPY_LOCATION src(resource, 0);
//        const CD3DX12_TEXTURE_COPY_LOCATION dst(staging.Get(), 0);
//        mList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
//
//        TransitionResource(mList.Get(), staging.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
//    }
//    else
//    {
//        // Resource is already a UAV so we can do this in-place
//        staging = resource;
//
//        TransitionResource(mList.Get(), staging.Get(), originalState, D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
//    }
//
//    // Create a descriptor heap that holds our resource descriptors
//    MyPtr<ID3D12DescriptorHeap> descriptorHeap;
//    D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
//    descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//    descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
//    descriptorHeapDesc.NumDescriptors = desc.MipLevels;
//    mDevice->CreateDescriptorHeap(&descriptorHeapDesc, IID_GRAPHICS_PPV_ARGS(descriptorHeap.GetAddressOf()));
//
//    SetDebugObjectName(descriptorHeap.Get(), L"ResourceUploadBatch");
//
//    auto const descriptorSize = static_cast<int>(mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
//
//    // Create the top-level SRV
//#if defined(_MSC_VER) || !defined(_WIN32)
//    CD3DX12_CPU_DESCRIPTOR_HANDLE handleIt(descriptorHeap->GetCPUDescriptorHandleForHeapStart());
//#else
//    CD3DX12_CPU_DESCRIPTOR_HANDLE handleIt;
//    std::ignore = descriptorHeap->GetCPUDescriptorHandleForHeapStart(&handleIt);
//#endif
//    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
//    srvDesc.Format = desc.Format;
//    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
//    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//    srvDesc.Texture2D.MostDetailedMip = 0;
//    srvDesc.Texture2D.MipLevels = desc.MipLevels;
//
//    mDevice->CreateShaderResourceView(staging.Get(), &srvDesc, handleIt);
//
//    // Create the UAVs for the tail
//    for (uint16_t mip = 1; mip < desc.MipLevels; ++mip)
//    {
//        D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
//        uavDesc.Format = desc.Format;
//        uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
//        uavDesc.Texture2D.MipSlice = mip;
//
//        handleIt.Offset(descriptorSize);
//        mDevice->CreateUnorderedAccessView(staging.Get(), nullptr, &uavDesc, handleIt);
//    }
//
//    // Set up UAV barrier (used in loop)
//    D3D12_RESOURCE_BARRIER barrierUAV = {};
//    barrierUAV.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
//    barrierUAV.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
//    barrierUAV.UAV.pResource = staging.Get();
//
//    // Barrier for transitioning the subresources to UAVs
//    D3D12_RESOURCE_BARRIER srv2uavDesc = {};
//    srv2uavDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
//    srv2uavDesc.Transition.pResource = staging.Get();
//    srv2uavDesc.Transition.Subresource = 0;
//    srv2uavDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
//    srv2uavDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
//
//    // Barrier for transitioning the subresources to SRVs
//    D3D12_RESOURCE_BARRIER uav2srvDesc = {};
//    uav2srvDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
//    uav2srvDesc.Transition.pResource = staging.Get();
//    uav2srvDesc.Transition.Subresource = 0;
//    uav2srvDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
//    uav2srvDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
//
//    // based on format, select srgb or not
//    ComPtr<ID3D12PipelineState> pso = mGenMipsResources->generateMipsPSO;
//
//    // Set up state
//    mList->SetComputeRootSignature(mGenMipsResources->rootSignature.Get());
//    mList->SetPipelineState(pso.Get());
//    mList->SetDescriptorHeaps(1, descriptorHeap.GetAddressOf());
//
//#if defined(_MSC_VER) || !defined(_WIN32)
//    D3D12_GPU_DESCRIPTOR_HANDLE handle(descriptorHeap->GetGPUDescriptorHandleForHeapStart());
//#else
//    D3D12_GPU_DESCRIPTOR_HANDLE handle;
//    std::ignore = descriptorHeap->GetGPUDescriptorHandleForHeapStart(&handle);
//#endif
//    mList->SetComputeRootDescriptorTable(GenerateMipsResources::SourceTexture, handle);
//
//    // Get the descriptor handle -- uavH will increment over each loop
//    CD3DX12_GPU_DESCRIPTOR_HANDLE uavH(handle, descriptorSize); // offset by 1 descriptor
//
//    // Process each mip
//    auto mipWidth = static_cast<uint32_t>(desc.Width);
//    uint32_t mipHeight = desc.Height;
//    for (uint32_t mip = 1; mip < desc.MipLevels; ++mip)
//    {
//        mipWidth = std::max<uint32_t>(1, mipWidth >> 1);
//        mipHeight = std::max<uint32_t>(1, mipHeight >> 1);
//
//        // Transition the mip to a UAV
//        srv2uavDesc.Transition.Subresource = mip;
//        mList->ResourceBarrier(1, &srv2uavDesc);
//
//        // Bind the mip subresources
//        mList->SetComputeRootDescriptorTable(GenerateMipsResources::TargetTexture, uavH);
//
//        // Set constants
//        GenerateMipsResources::ConstantData constants;
//        constants.SrcMipIndex = mip - 1;
//        constants.InvOutTexelSize = XMFLOAT2(1 / float(mipWidth), 1 / float(mipHeight));
//        mList->SetComputeRoot32BitConstants(
//            GenerateMipsResources::Constants,
//            GenerateMipsResources::Num32BitConstants,
//            &constants,
//            0);
//
//        // Process this mip
//        mList->Dispatch(
//            (mipWidth + GenerateMipsResources::ThreadGroupSize - 1) / GenerateMipsResources::ThreadGroupSize,
//            (mipHeight + GenerateMipsResources::ThreadGroupSize - 1) / GenerateMipsResources::ThreadGroupSize,
//            1);
//
//        mList->ResourceBarrier(1, &barrierUAV);
//
//        // Transition the mip to an SRV
//        uav2srvDesc.Transition.Subresource = mip;
//        mList->ResourceBarrier(1, &uav2srvDesc);
//
//        // Offset the descriptor heap handles
//        uavH.Offset(descriptorSize);
//    }
//
//    // If the staging resource is NOT the same as the resource, we need to copy everything back
//    if (staging.Get() != resource)
//    {
//        // Transition the resources ready for copy
//        D3D12_RESOURCE_BARRIER barrier[2] = {};
//        barrier[0].Type = barrier[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
//        barrier[0].Transition.Subresource = barrier[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
//        barrier[0].Transition.pResource = staging.Get();
//        barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
//        barrier[0].Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE;
//
//        barrier[1].Transition.pResource = resource;
//        barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_SOURCE;
//        barrier[1].Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
//
//        mList->ResourceBarrier(2, barrier);
//
//        // Copy the entire resource back
//        mList->CopyResource(resource, staging.Get());
//
//        // Transition the target resource back to pixel shader resource
//        TransitionResource(mList.Get(), resource, D3D12_RESOURCE_STATE_COPY_DEST, originalState);
//
//        mTrackedObjects.push_back(staging);
//    }
//    else
//    {
//        TransitionResource(mList.Get(), staging.Get(), D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, originalState);
//    }
//
//    // Add our temporary objects to the deferred deletion queue
//    mTrackedObjects.push_back(mGenMipsResources->rootSignature);
//    mTrackedObjects.push_back(pso);
//    mTrackedObjects.push_back(resource);
//    mTrackedObjects.push_back(descriptorHeap);
//}