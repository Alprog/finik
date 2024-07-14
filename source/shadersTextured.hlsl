
cbuffer ConstantBuffer : register(b0)
{
	row_major float4x4 MVP;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

PSInput VSMain(float3 position : POSITION, float4 uv : TEXCOORD)
{
	PSInput result;

	result.position = float4(position, 1); //mul(float4(position, 1), MVP);
	result.uv = uv;

	return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
	return float4(1, 0, 0, 1);// g_texture.Sample(g_sampler, input.uv);
}
