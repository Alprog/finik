#pragma pack_matrix( row_major )

cbuffer ConstantBuffer : register(b0)
{
	float4x4 MVP;
};

struct VSInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float4 uv : TEXCOORD;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

PSInput VSMain(VSInput input)
{
	PSInput result;

	result.position = mul(float4(input.position, 1), MVP);
	result.normal = input.normal;
	result.uv = input.uv;

	result.position /= result.position.w;

	result.position.z = 0.1; // temp

	return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
	if (input.position.z == 0)
		return 1;

	float4 color = float4(input.normal, 1);
	color.rgb = (color.rgb + 1) / 2;
	return color;// g_texture.Sample(g_sampler, input.uv);
}
