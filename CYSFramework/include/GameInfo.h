#pragma once

// 미리 컴파일된 헤더
#include <Windows.h>

 // 자료구조 리스트
#include <list>
#include <vector>
#include <unordered_map>	// 해쉬 트리
#include <map>				// 기본 트리
#include <string>

#include "Vector2D.h"

// RELEASE 매크로
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr;}

// DX를 사용하기 위한 헤더
#include <d3d11.h>
#include <d3dcompiler.h>

/*
	라이브러리를 가져와서 사용하는 방식이다.
	lib, dll

	lib : 정적 라이브러리
	프로그램 빌드 시점에서 실행파일에 코드가 직접 포함된다.

	dll : 동적 라이브러리
	프로그램 시작되면 그때 메모리에 별도로 로드된다. 런타임중 기능을 불러온다. 프로그램 빌드시 코드가 포함은 안된다.
	dll은 배포할때 dll 파일을 같이 배포해줘야한다.
*/

// .lib를 통해서 DX11 기능을 불러와야 한다.
// 링크를 거는 방법
#pragma comment(lib, "d3d11.lib");			// DX11 기능을 포함하는 애
// DX11은 쉐이더를 별도로 컴파일 해줘야 하므로, 그 컴파일을 하기 위해서 필요하다.
// 왜? 쉐이더는 hlsl 이라는 언어로 작성되기 때문에 해당 언어를 컴파일 하기 위해서 추가한다.
#pragma comment(lib, "d3dcompiler.lib");
// GUID를 사용하기 위해서 필요하다.
#pragma comment(lib, "dxguid.lib");



// 마이어스 싱글톤
#define DECLARE_SINGLETON(ClassName)\
private:\
	ClassName();\
	~ClassName();\
public:\
	static ClassName* GetInst()\
	{\
		static ClassName instance;\
		return &instance;\
	}

struct FRect
{
	float Left = 0.f;
	float Top = 0.f;
	float Right = 0.f;
	float Bottom = 0.f;
};

enum class EBulletOption
{
	Normal,
	Bound,
	Wave,
	Storm
};

struct FBullet
{
	FVector2D Pos;
	FVector2D Size;
	FVector2D MoveDir;

	FVector2D Center;

	float Distance = 500.f;	// 사정거리
	EBulletOption Option = EBulletOption::Normal;

	float AccTime = 0;
};

struct BulletInfo
{
	FVector2D Dir;
	FVector2D OffSet;

	BulletInfo(FVector2D _Dir, FVector2D _OffSet)
		: Dir(_Dir), OffSet(_OffSet) {}
};

// 해상도 저장 구조체
struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};