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
    // permanent
    UnboundTextureTable,
    MaterialsConstantBufferView,

    // per frame
    FrameConstantBufferView,
    
    // per draw
    MeshConstantBufferView,
    MaterialInlineConstants,
    
    Count
};