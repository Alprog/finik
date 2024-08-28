#pragma pack_matrix( row_major )

cbuffer MeshConstantBuffer : register(b0)
{
	float4x4 Model;
};

cbuffer FrameConstantBuffer : register(b1)
{
	float4x4 ViewProject;
};

struct VSInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float4 uv : TEXCOORD0;
	uint2 coord : TEXCOORD1;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;
	uint2 coord : TEXCOORD2;
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
Texture2D gridTexture : register(t1);

PSInput VSMain(VSInput input)
{
	PSInput result;

	float4x4 MVP = mul(Model, ViewProject);

	result.position = mul(float4(input.position, 1), MVP);
	result.normal = input.normal;
	result.uv = input.uv;
	result.coord = input.coord;

	return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
	if (input.position.z == 0)
		return 1;

	
	float3 fillColor = gridTexture.Sample(g_sampler, float2(input.coord) / 256).rgb;
	float3 borderColor = g_texture.Sample(g_sampler, input.uv).rgb;
	
	return float4(fillColor + borderColor, 1);	
}
