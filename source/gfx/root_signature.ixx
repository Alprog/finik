export module root_signature;

import dx;
import render_system_fwd;

export class RootSignature
{
public:
    RootSignature(RenderSystem& renderSystem);

    MyPtr<ID3D12RootSignature> signatureImpl;
};
