/****	Texture	****/
Texture2D g_Tex : register(t0);

/****	Sampler	****/
SamplerState g_SamplerLinear : register(s0);

/****	VertexShaderOutput	****/
struct VS_OUTPUT
{
	float4	Position :  SV_POSITION;
	float4	Color	:	TEXCOORD1;
	float2  Tex		:   TEXCOORD2;
};