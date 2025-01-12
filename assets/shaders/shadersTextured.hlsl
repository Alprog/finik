#include "shaders/common.inc"

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
	
	return color;
	
	Texture2D mainTexture = textures[Materials[MaterialId].TextureA];
	float4 texColor = mainTexture.Sample(g_sampler, input.uv);
	
	float4 diffuseColor = lerp(color, texColor, 1);
	
	float diffuse = 0.2 + (dot(input.normal, -LightDirection) + 1) * 0.4;
	
	return diffuse * diffuseColor;
}
