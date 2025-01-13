
SamplerState DefaultSampler : register(s0);
SamplerState PointSampler : register(s1);
SamplerState LinearSampler : register(s2);

Texture2D<float4> SrcMip   : register(t0);
RWTexture2D<float4> OutMip : register(u0);

cbuffer MipConstants : register(b0)
{
    float2 InvOutTexelSize; // texel size for OutMip
    uint SrcMipIndex;
}

float4 Mip(uint2 coord)
{
    float2 uv = (coord.xy + 0.5) * InvOutTexelSize;
    return SrcMip.SampleLevel(LinearSampler, uv, SrcMipIndex);
}

[numthreads(8, 8, 1)]
void CSMain(uint3 coord : SV_DispatchThreadID)
{
    OutMip[coord.xy] = Mip(coord.xy);
}