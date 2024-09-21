#pragma once

import math;

struct MeshConstantBuffer
{
    Matrix Model;
};

struct FrameConstantBuffer
{
    Matrix View;
    Matrix Projection;
    Matrix ViewProjection;
};

enum RootSignatureParams
{
    MeshInlinedConstants = 0,
    FrameConstantBufferView = 1,
    TextureView1 = 2,
    TextureView2 = 3
};