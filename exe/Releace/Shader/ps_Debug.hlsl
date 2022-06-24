#include "psvsCommon.hlsl"
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 ps_Debug(VS_DEBUG_OUTPUT input) : SV_Target
{
    float4 output;
    output = input.Color;
    output.a = 0.5f;
    return output;
}
