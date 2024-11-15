#pragma pack_matrix( row_major )

cbuffer MeshConstantBuffer : register(b0)
{
	float4x4 Model;
};

cbuffer FrameConstantBuffer : register(b1)
{
	float4x4 View;
	float4x4 Projection;
	float4x4 ViewProject;
};

cbuffer MaterialConstantBuffer : register(b2)
{
    int TextureId; 
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
Texture2D gridTexture : register(t1);

Texture2D textures[] : register(t0, space1);