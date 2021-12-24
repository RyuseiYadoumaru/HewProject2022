#include "psvsCommon.hlsl"
#include "ConstantBuffer.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

VS_OUTPUT vs_Ui(float4 Pos : POSITION, float4 Color : COLOR, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

	/****	座標変換	****/
    float4 ScreenPos = mul(World, Pos);
	
	/****	スクリーン座標変換	****/
    output.Position.x = (2.0f / (float) ViewportWidth.x) * ScreenPos.x - 1.0f;
    output.Position.y = 1.0f - ((2.0f / (float) ViewportHeight.x) * ScreenPos.y);
    output.Position.z = Pos.z;
    output.Position.w = 1.0f;

    output.Color = Color;
    output.Tex = Tex;
    return output;
}