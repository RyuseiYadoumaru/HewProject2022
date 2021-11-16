#include "psvsCommon.hlsl"

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 ps_2DSprite(VS_OUTPUT input) : SV_Target
{

	float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
	return texcol * input.Color;

}

