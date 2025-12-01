#include "Share.fx"

struct VS_Input_Tex
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VS_Output_Tex
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

// UI용 상수버퍼
cbuffer UI : register(b3)   // 스프라이트가 b3이지만 다 써버렸으니 다시 돌려서 쓰기 가능
{
	// Tint : 텍스쳐에 대한 보정 색상
    float4 gBrushTint; // 16 

	// Widget에 대한 보정 색상
    float4 gWidgetColor; // 16

    // Lef-Top
    float2 gBrushAnimLTUV; // 8

	// Right-Bottom
    float2 gBrushAnimRBUV; // 8

	// 애니메이션 사용여부
    int gBrushAnimEnable; // 4

    // 텍스쳐 사용 여부
    int gBrushTextureEnable; // 4

    // 애니메이션 반전 여부
    // int gBrushAnimFlip;

	// 빈 데이터 16배수로 보내줘야한다.
    float2 gBrushEmpty;
}

float2 UpdateAnimationUI(float2 UV)
{
    if (gBrushAnimEnable == 0)
    {
        return UV;
    }

    float2 Result = (float2) 0.f;

    if (UV.x == 0.f) // 좌
    {
        Result.x = gBrushAnimLTUV.x;
    }
    else // 우
    {
        Result.x = gBrushAnimRBUV.x;
    }

    if (UV.y == 0.f) // 위
    {
        Result.y = gBrushAnimLTUV.y;
    }
    else // 아래
    {
        Result.y = gBrushAnimRBUV.y;
    }

    return Result;
}

VS_Output_Tex UIVS(VS_Input_Tex input)
{
    VS_Output_Tex output = (VS_Output_Tex) 0;

    float3 Pos = input.Pos - gPivot;

    output.Pos = mul(float4(Pos, 1.f), gmatWVP);

    output.UV = UpdateAnimationUI(input.UV);
    
    return output;
}

PS_Output_Single UIPS(VS_Output_Tex input)
{
    PS_Output_Single output = (PS_Output_Single) 0;

    float4 Color = float4(1.f, 1.f, 1.f, 1.f);

    if (gBrushTextureEnable)
    {
        Color = gBaseTexture.Sample(gBaseSampler, input.UV);
    }

    output.Color = Color * gBrushTint * gWidgetColor;
    
    return output;
}