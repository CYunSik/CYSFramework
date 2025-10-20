#include "Share.fx"

// 정점 정보
// 위치 색상
// 위치 12바이트
// 색상 16바이트
// 이 정보로 시멘틱을 만들어둔다.

struct VS_Input_Color
{
    float3 Pos : POSITIONT; // POSITION 0번 레지스터
    float4 Color : COLOR;   // COLOR 0번 레지스터
};

// 정점 쉐이더의 반환 값
struct VS_Output_Color
{
    // 위치 값이 float4가 되는 이유 : 투영 단계에서 w값도 포함되어야 하기 때문이다.
    // SV를 붙여줘야 레스터라이즈 단계에서 얘가 위치 값이다. 를 인식한다.
    // 만약 SV를 안 붙이고 일반 POSITION이라고 한다면 레스터라이즈 단계에서 이게 사용할 위치값인지 아닌지 모른다.
    float4 Pos : SV_Position;    // SV_POSITION 0번 레지스터
    float4 Color : COLOR;        // COLOR 0번 레지스터
};

VS_Output_Color ColorMeshVS(VS_Input_Color input)
{
    // 초기화
    VS_Output_Color output = (VS_Output_Color) 0;
    
    output.Pos = float4(input.Pos, 1.f);
    output.Color = input.Color;
    
    return output;
}

// 중간에 레스터라이즈 단계는 알아서 해준다.

PS_Output_Single ColorMeshPS(VS_Output_Color input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    output.Color = input.Color;
    
    return output;
}

// 속성
// 진입점 main -> 시작할 정점쉐이더(ColorMeshVS)
// 쉐이더 형식 -> 효과(/fx)
// 쉐이도 모델 5.0