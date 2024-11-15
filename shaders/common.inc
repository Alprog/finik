#pragma pack_matrix( row_major )

struct Material
{
    float4 ColorA;
    float4 ColorB;
    float4 ColorC;
    float4 ColorD;
    uint TextureA;
    uint TextureB;
    uint TextureC;
    uint TextureD;
};

// permanent
Texture2D textures[] : register(t0, space1);

cbuffer MaterialsConstantBuffer : register(b3)
{
    Material Materials[80];
};

// per frame
cbuffer FrameConstantBuffer : register(b1)
{
	float4x4 View;
	float4x4 Projection;
	float4x4 ViewProject;
};

// per draw
cbuffer MeshConstantBuffer : register(b0)
{
	float4x4 Model;
};

cbuffer MaterialConstantBuffer : register(b2)
{
    int TextureId; 
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

