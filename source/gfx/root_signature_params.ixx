export module root_signature_params;

import core;

export struct MeshConstants
{
    Matrix Model;
};

export struct FrameConstants
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