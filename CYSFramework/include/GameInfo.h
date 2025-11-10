#pragma once

// 미리 컴파일된 헤더
#include <Windows.h>

 // 자료구조 리스트
#include <list>
#include <vector>
#include <map>				// 기본 트리
#include <unordered_map>	// 해쉬 트리
#include <crtdbg.h>
#include <functional>

#include <string>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix.h"

#include "Share/SharedPtr.h"

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
#pragma comment(lib, "d3d11.lib")			// DX11 기능을 포함하는 애
// DX11은 쉐이더를 별도로 컴파일 해줘야 하므로, 그 컴파일을 하기 위해서 필요하다.
// 왜? 쉐이더는 hlsl 이라는 언어로 작성되기 때문에 해당 언어를 컴파일 하기 위해서 추가한다.
#pragma comment(lib, "d3dcompiler.lib")
// GUID를 사용하기 위해서 필요하다.
#pragma comment(lib, "dxguid.lib")

// RELEASE 매크로
#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr;}

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

// 해상도 저장 구조체
struct FResolution
{
	unsigned int Width = 0;
	unsigned int Height = 0;
};

// 정점 버퍼 vertex buffer
struct FVertexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	void* Data = nullptr;

	FVertexBuffer() = default;
	~FVertexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

// 인덱스 버퍼
struct FIndexBuffer
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	int Count = 0;
	DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN;
	void* Data = nullptr;

	FIndexBuffer() = default;
	~FIndexBuffer()
	{
		SAFE_RELEASE(Buffer);
		SAFE_DELETE_ARRAY(Data);
	}
};

// 정점의 정보를 저장하는 구조체
struct FVertexColor
{
	FVector3D Pos;
	FVector4D Color;

	FVertexColor()
	{

	}

	FVertexColor(const FVector3D& _Pos, const FVector4D& _Color)
		: Pos(_Pos), Color(_Color)
	{

	}

	FVertexColor(float x, float y, float z, float r, float g, float b, float a)
		: Pos(x, y, z), Color(r, g, b, a)
	{

	}
};

namespace EShaderBufferType
{
	enum Type
	{
		Vertex = 0x1,	// 첫번째 비트값
		Pixel = 0x2,	// 두번째 비트값
		Hull = 0x4,		// 세번째 비트값
		Domain = 0x8,	// ...
		Geometry = 0x10,
		Compute = 0x20,
		Graphic = Vertex | Pixel | Hull | Domain | Geometry,
		All = Vertex | Pixel | Hull | Domain | Geometry | Compute
	};
}

// 충돌
enum class EColliderType
{
	Collider2D,
	Collider3D
};

// 충돌 모양
enum class EColliderShape
{
	AABB2D,
	Sphere2D,
	OBB2D
};

// 충돌 정보
struct FAABB2D
{
	FVector2D Min;	// 왼쪽 아래 점
	FVector2D Max;	// 오른쪽 위 점
};

struct FOBB2D
{
	// 중심점
	FVector2D Center;
	// 축 인덱스 0 : X축		인덱스 1 : Y축
	FVector2D Axis[2];
	// 길이의 반
	FVector2D HalfSize;
};

// 충돌 필터 정보
// 채널
namespace ECollisionChannel
{
	// enum값은 기본형으로 정수
	// 옆에 : 넣으면 지정한 자료형으로
	enum Type : unsigned char
	{
		Default,
		Player,
		Monster,
		PlayerAttack,
		MonsterAttack,
		End
	};
}

// 상호작용 : 충돌체끼리 충돌을 할지 말지 저장
namespace ECollisionInteraction
{
	enum Type : unsigned char
	{
		Ignore,		// 충돌 무시
		Collision,	// 충돌
		End
	};
}


/*
	Player꺼 프로파일을 만들고 채널을 Player로 지정했다.
	이때 다른 채널을 사용하는 프로파일과 충돌해야할지 여부에 따라서
	충돌 함수를 호출해 줄 것이다.

	다른 채널과 어떻게 되어 있는지는 미리 저장해야 한다.

	// 1번 프로파일 플레이어 충돌정보
	Channel : Player
	Enable : true
	Interaction[Default] = Collision;
	Interaction[Player] = Ignore;
	Interaction[Monster] = Ignore;
	Interaction[PlayerAttack] = Ignore;
	Interaction[MonsterAttack] = Collision;

	// 2번 프로파일 몬스터 공격 프로파일
	Channel : MonsterAttack
	Enable : true
	Interaction[Default] = Collision;
	Interaction[Player] = Collision;
	Interaction[Monster] = Ignore;
	Interaction[PlayerAttack] = Ignore;
	Interaction[MonsterAttack] = Collision;

	if(Player->Interaction[MonsterAttck] == Collision && MonsterAttck->Interaction[Player] == Collision)
	// 충돌했다!!
*/

// 프로파일
// 채널과 상호작용을 이용해서 프로파일을 만들어준다.
// 미리 등록시키는 형식(시스템)이다.
struct FCollisionProfile
{
	std::string Name;
	// 현재 프로파일이 사용하는 충돌 채널
	ECollisionChannel::Type Channel = ECollisionChannel::Default;
	bool Enable = true;
	ECollisionInteraction::Type Interaction[ECollisionChannel::End];
};