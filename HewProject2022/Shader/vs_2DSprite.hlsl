#include "psvsCommon.hlsl"
#include "ConstantBuffer.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

VS_OUTPUT vs_2DSprite(float4 Pos : POSITION, float4 Color : COLOR, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    float4 ScreenPos;

	/****	座標変換	****/
    float4 WorldPos = mul(World, Pos);
	//ScreenPos = mul(View, WorldPos);
    ScreenPos.x = WorldPos.x - (CameraPos.x - (ViewportWidth / 2.0f));
    ScreenPos.y = WorldPos.y - (CameraPos.y - (ViewportHeight / 2.0f));
	
	/****	スクリーン座標変換	****/
    output.Position.x = (2.0f / (float) ViewportWidth.x) * ScreenPos.x - 1.0f;
    output.Position.y = 1.0f - ((2.0f / (float) ViewportHeight.x) * ScreenPos.y);
    output.Position.z = Pos.z;
    output.Position.w = 1.0f;

    output.Color = Color;
    output.Tex = Tex;
    return output;
}