
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