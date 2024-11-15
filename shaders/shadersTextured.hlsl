#include "common.inc"

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

PSInput VSMain(VSInput input)
{
	PSInput result;
	
	float4x4 MVP = mul(Model, ViewProject);

	result.position = mul(float4(input.position, 1), MVP);
	result.normal = input.normal;
	result.uv = input.uv;

	return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
	if (input.position.z == 0)
		return 1;

	float4 color = float4(input.normal, 1);
	color.rgb = (color.rgb + 1) / 2;
	
	float4 texColor = g_texture.Sample(g_sampler, input.uv);
	
	return lerp(color, texColor, 0.5);
}
