export module root_signature_params;

import core;

// for intellisense

export struct MeshConstants
{
    Matrix Model;
};

export struct FrameConstants
{
    Matrix ViewProjection;
    Matrix View;
    Matrix Projection;
    Vector4 LightDirection;
};