/*
    화면에 출력되는 과정을 렌더링 파이프라인이라고 불린다.
    쉐이더는 GPU가 실행해주는 프로그램

    렌더링 파이프라인
    버텍스 쉐이더 : 정점을 정해주는 쉐이더 V

    헐 쉐이더 : 테셀레이션 이전의 단계 V
    테셀레이션 : 얼마나 삼각형을 쪼갤건지 포폴에서는 필요X 까다로움
    도메인 쉐이더 : 테셀레이션 단계의 끝, 테셀레이션의 위치값을 최종 계산 V

    지오메트리(기하) 쉐이더 : 여러 점을 조작할 수 있는 쉐이더 V
    레스터 라이즈 : 최종적으로 화면에 색을 출력하기 위한 단계, 점과 선을 최종적으로 계산하고 뷰포트 변환이 여기서 일어난다, 색을 칠할 준비한다.
    픽셀 쉐이더 : 최종 색을 결정한다. V

    컴퓨트 쉐이더 : 렌더링 파이프라인에 관련이 없는 편이다, 그래픽카드에 연산만 시키는 전용

    정점 쉐이더 : 정점의 변환을 담당한다.

    좌표계
    월드 변환 ( 로컬 좌표 -> 월드 좌표 )
       
    뷰 변환 ( 월드 좌표 -> 카메라 좌표, 카메라가 보는 물체만 나오게 한다. )
    
    투영 변환 ( 1. 카메라 좌표 -> 클립 좌표 -> 2. 원근 나누기 x y z w 중 w값을 이용해서 원근감을 적용 )

    변환은 전부 행렬로 이루어진다.

    V : 개발자가 쉐이더 코드를 작성한다.
*/

struct PS_Output_Single
{
    // 자료형 변수명 : 시멘틱
    // SV : 시스템 밸류 (시스템에 자동으로 넣어주는 값)
    // SV_TARGET을 하면 뒤에 0이 생략 된다. 숫자는 레지스터 넘버이다.
    // SV_TARGET0
    // 시멘틱을 통해서 내가 원하는 레지스터에 등록할 수 있다.
    float4 Color : SV_TARGET;
};

/////////////////////////////////
// 상수 레지스터
// 상수 버퍼
// C++의 값을 쉐이더로 보낼때 사용한다.
// 상수 버퍼와 구조화 버퍼(지금은 안씀) 등이 있다.

// 상수 레지스터 0번을 사용하겠다.
cbuffer Transform : register(b0)
{
    matrix gmatWorld;   // 월드 행렬
    matrix gmatView;    // 카메라(뷰) 행렬
    matrix gmatProj;    // 투영(프로젝션) 행렬
    matrix gmatWV;      // 월드 * 카메라
    matrix gmatWVP;     // 월드 * 카메라 * 투영
    float3 gPivot;      // 피봇
    float gTransformEmpty;
}

cbuffer Material : register(b1)
{
	// 재질 기본 색상
    float4 gMtrlBaseColor;
	// 재질 투명도
    float gMtrlOpacity;
    // 재질 텍스쳐 가로 크기
    int gMtrlTextureWidth;
	// 재질 텍스쳐 세로 크기
    int gMtrlTextureHeight;
    // 16바이트 맞추기용 더미 하나 추가해준다.
    float gMtrlEmpty;
}

cbuffer Animation2D : register(b2)
{
	// Lef-Top
    float2 gAnim2DLTUV; // 8

	// Right-Bottom
    float2 gAnim2DRBUV; // 8

	// 애니메이션 사용여부
    int gAnim2DEnable; // 4

    // 애니메이션 반전 여부
    int gAnim2DFlip;

	// 빈 데이터 16배수로 보내줘야한다.
    float2 Empty;
}

// 샘플러
SamplerState gBaseSampler : register(s0);

// 텍스쳐
Texture2D gBaseTexture : register(t0);
// 나중에 더 사용하려면 추가
//Texture2D gBaseTexture2 : register(t1);
//Texture2D gBaseTexture3 : register(t2);
//Texture2D gBaseTexture4 : register(t3);

float2 UpdateAnimation2D(float2 UV)
{
    if (gAnim2DEnable == 0)
    {
        return UV;
    }

    float2 Result = (float2) 0.f;

    if (UV.x == 0.f) // 좌
    {
        Result.x = gAnim2DLTUV.x;
    }
    else // 우
    {
        Result.x = gAnim2DRBUV.x;
    }

    if (UV.y == 0.f) // 위
    {
        Result.y = gAnim2DLTUV.y;
    }
    else // 아래
    {
        Result.y = gAnim2DRBUV.y;
    }

    return Result;
}