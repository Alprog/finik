export module root_signature_params;

import core;

export struct MeshConstantBuffer
{
    Matrix Model;
};

export struct FrameConstantBuffer
{
    Matrix View;
    Matrix Projection;
    Matrix ViewProjection;
};

export enum RootSignatureParams
{
    MeshConstantBufferView = 0,
    FrameConstantBufferView = 1,
    TextureView1 = 2,
    TextureView2 = 3,
    TextureArray = 4,
    MaterialInlineConstants = 5,
    
    Count
};