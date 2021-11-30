#include "psvsCommon.hlsl"
#include "ConstantBuffer.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------

VS_DEBUG_OUTPUT vs_Debug(float4 Pos : POSITION, float4 Color : COLOR)
{
    VS_DEBUG_OUTPUT output = (VS_DEBUG_OUTPUT) 0;

    float4 ScreenPos;

    //ScreenPos = mul(View, WorldPos);
    ScreenPos.x = Pos.x - (CameraPos.x - (ViewportWidth / 2.0f));
    ScreenPos.y = Pos.y - (CameraPos.y - (ViewportHeight / 2.0f));
	
	/****	スクリーン座標変換	****/
    output.Position.x = (2.0f / (float) ViewportWidth.x) * ScreenPos.x - 1.0f;
    output.Position.y = 1.0f - ((2.0f / (float) ViewportHeight.x) * ScreenPos.y);
    output.Position.z = Pos.z;
    output.Position.w = 1.0f;

    output.Color = Color;
    
    return output;
}